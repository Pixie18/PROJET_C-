#include "client.hpp"

Client::Client(QString username, QString ip, int port){
  this->username = username;
  user_id = -1;
  server_ip = ip;
  server_port = port;
  sock = new QTcpSocket();

  OpenSocket();
  ConnectSignals();
}

void Client::ConnectSignals(){
  connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(RetryOpenSocket()));
  connect(sock, SIGNAL(connected()), this, SLOT(ConnectApp()));
  connect(sock, SIGNAL(readyRead()), this, SLOT(ReadPackets()));

}
void Client::OpenSocket(){
  static char tryCount = 5;
  
  qDebug() << "Try connection " << tryCount;
  if (--tryCount <= 0)
    qApp->quit();
  
  sock->connectToHost(QString(server_ip), server_port);
}

void Client::SendPacket(int message_code, QString message){
  struct app_proto packet;
  
  packet.msg_code = message_code;
  packet.user_id = user_id;
  strcpy(packet.data, message.toStdString().c_str());
  packet.data[message.length()] = '\0';
  
  sock->write((char*)&packet, 8+message.length()+1);
}

void Client::ConnectApp(){
  disconnect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(RetryOpenSocket()));
  SendPacket(CONNECT);
}

void Client::SendName(){
  SendPacket(NAME, username);
}

void Client::SendMessage(QString msg){
  qDebug() << "Envoie d'un message: " << msg;
  SendPacket(MESSAGE, msg); 
}

void Client::Disconnect(){
  SendPacket(DISCONNECT, username);
}
void Client::RetryOpenSocket(){
  OpenSocket();
}

void Client::ReadPackets(){
  struct app_proto packet;
  while(sock->bytesAvailable()){
    qDebug() << sock->read((char*)&packet, sizeof(struct app_proto));

    switch(packet.msg_code){
      case CONNECT_ACK:
        SendName();
        break;
      
      case NAME_ACK:
        qDebug() << packet.data << " vient de se connecter";
        if (packet.data == username)
          user_id = packet.user_id;
        users_list[packet.user_id] = packet.data;
        break;

      case MESSAGE_ACK:
        qDebug() << "Un message vient d'etre recu: " << packet.data;
        emit(newMessage(users_list[packet.user_id] + "> " + packet.data));
        break;
      
      case DISCONNECT_ACK:
        qDebug() << packet.data << " vient de se deconnecter";
        users_list.remove(packet.user_id);
        if (packet.user_id == user_id){
          sock->close();
          qApp->quit();
        }
    }
  }
}
