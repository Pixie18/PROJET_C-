#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QApplication>
#include <QString>

class Client : public QObject{
  Q_OBJECT

  public:

    /* Constructure de la classe prenant en paramètre le nom de l'utilisateur,
     * l'adresse ip et le port du serveur sur lequel le client se connecte.
     */
    Client(QString username, QString ip, int port);

    /* Méthode pour ouvrir et se connecter au serveur.
     */
    void OpenSocket();

    /* Construit et envoie un packet sur la socket de client.
     */
    void SendPacket(int message_code, QString message = "");

    /* Fonction connectant les signaux (listener) interne à la class à ses slots
     * (fonction de callback).
     */
    void ConnectSignals();

  public:

    // Définition du packet de protocole utilisé par l'application.
    struct app_proto{
      int msg_code;
      int user_id;
      char data[4096];
    };
    
    // Définition des types message du protocole utilisé par l'application.
    enum {CONNECT, CONNECT_ACK, NAME, NAME_ACK, MESSAGE, MESSAGE_ACK,
      DISCONNECT, DISCONNECT_ACK};

    
  private:
    
    // Identifiant donnée par le serveur au client connecté.
    int user_id;

    // Port du serveur sur lequel le client se connecte.
    int server_port;

    // Adress du serveur sur lequel le client se connect.
    QString server_ip;

    // Nom d'utilisateur de client.
    QString username;

    // Socket TCP gérant la connexion avec le serveur.
    QTcpSocket *sock;

    // Liste rassemblant les noms des utilisateurs connectés au serveur.
    QMap<int, QString> users_list;

  public slots:
    
    /* Fonction appellée lorsque la connexion TCP avec le serveur est réussie.
     * Elle permet d'envoyer le message de connexion de la couche applicative.
     */
    void ConnectApp();

    /* Cette fonction est utilisée lorsque la connexion TCP n'à pas pu être
     * établie. Elle permet de relancer la fonction méthode d'ouverture de la
     * socket.
     */
    void RetryOpenSocket();

    /* Envoie un message NAME au serveur. */
    void SendName();

    /* Envoie un message MESSAGE au serveur */
    void SendMessage(QString msg);

    /* Envoie un message DISCONNECT au serveur. */
    void Disconnect();

    /* Fonction utilisée pour lire les paquets en attentes dans le buffer
     * d'entrée de la socket.
     */
    void ReadPackets();
  
  signals:
    /* Signal récupérer par la fenêtre principale afin d'afficher le message
     * reçu sur la fenêtre de chat.
     */
    void newMessage(QString msg);

};
#endif
