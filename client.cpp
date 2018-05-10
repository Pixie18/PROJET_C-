#include "client.hpp"

Client::Client(QString username, QString ip, int port){/*constructeur*/
  this->username = username;/*ici le this est utile pcq je pointe sur username passé en param : pour le distinguer vu que c'est pas le m^*/
  user_id = -1;/*pcq il sera fourni par le serveur nous l'enverra après*/
  server_ip = ip;
  server_port = port;
  sock = new QTcpSocket();

  OpenSocket();
  ConnectSignals();/*pour les connecter soit içi soit dans le controller*/
}

void Client::ConnectSignals(){
  connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(RetryOpenSocket()));/*si il y a une erreur lors de la conx : probleme de conx au serveur slot pour me reconnecter*/
  connect(sock, SIGNAL(connected()), this, SLOT(ConnectApp()));/*déconnecter sinn il va pas s'arreter : connectappp me permet d'envoyer le msg au niveau apllicatif*/
  connect(sock, SIGNAL(readyRead()), this, SLOT(ReadPackets()));/*m'informer lorsk j'ai un msg a lire ds la socket*/

}
void Client::OpenSocket(){/*pour ouvrir la socket j'utilise la fct connectToHost pour connecter le client au serveur*/
  static char tryCount = 5;
  
  qDebug() << "Try connection " << tryCount; /*c'est juste pour afficher un msg que la connexion est en cours */
  if (--tryCount <= 0)
    qApp->quit();
  
  sock->connectToHost(QString(server_ip), server_port);
}

void Client::SendPacket(int message_code, QString message){ /*méthode pour envoyer des paquets, chaque paquet à un code : message_code*/ 
  struct app_proto packet; /*je crée mon paquet : cette structure est déclarée dans client.hpp*/
  
  packet.msg_code = message_code;/*je met le msg_code*/
  packet.user_id = user_id;
  strcpy(packet.data, message.toStdString().c_str());/*je copie les données de mon msg dans data, je le transfomre d'abord le string en tableau de char pck le message est un objet de "qstring" et la fonction strcpy est une méth standar*/
  packet.data[message.length()] = '\0';
  
  sock->write((char*)&packet, 8+message.length()+1);/*une foie le packet contrui je l'envoi dans la socket avec la méthode write pas send , 8+message.length()+1 longuer des données l'entet+ la longuer du msg*/
}

void Client::ConnectApp(){/*permet : le slot est activé qd je reçoi un signal de connection*/
  disconnect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(RetryOpenSocket()));/*voir av mia*/
  SendPacket(CONNECT);
}

void Client::SendName(){/*envoi un paquet de type name*/
  SendPacket(NAME, username);
}

void Client::SendMessage(QString msg){/*envoi un paquet de type msg*/
  qDebug() << "Envoie d'un message: " << msg;
  SendPacket(MESSAGE, msg); 
}

void Client::Disconnect(){/*permet de se deco du serveur */
  SendPacket(DISCONNECT, username);
}
void Client::RetryOpenSocket(){/*permet de réssyer de se conncter ne cas d'erreur*/
  OpenSocket();
}

void Client::ReadPackets(){/*boucle principal :la fct qui va gérer : on utilise boucle pcq qd plsr signaux déclenche un fct la fct est appelé plusieru fois*/
  struct app_proto packet;
  while(sock->bytesAvailable()){
    qDebug() << sock->read((char*)&packet, sizeof(struct app_proto));/*lit le paquet*/

    switch(packet.msg_code){/*si on a reçu un msg connect_ack en envoi notre nom*/
      case CONNECT_ACK:
        SendName();
        break;
      
      case NAME_ACK:
        qDebug() << packet.data << " vient de se connecter";
        if (packet.data == username)
          user_id = packet.user_id;/*je récupère le user_id que le serveur m'envoi*/
          users_list[packet.user_id] = packet.data;/*etje le rajoute dans la liste des users*/
        break;

      case MESSAGE_ACK:
        qDebug() << "Un message vient d'etre recu: " << packet.data;
        emit(newMessage(users_list[packet.user_id] + "> " + packet.data)); /*j'affiche le contenu du msg et j'émi un signal pour notifier a l'interfce graph de semttre a jour et d'affciher le nv msg*/
        break;
      
      case DISCONNECT_ACK:
        qDebug() << packet.data << " vient de se deconnecter";
        users_list.remove(packet.user_id);/*si c'est un user qui s'est déconnété -> je le retir de la liste*/
        if (packet.user_id == user_id){/*si c'est moi qui s'est déconnecter je ferme*/
          sock->close();
          qApp->quit();
        }
    }
  }
}
