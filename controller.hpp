#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QApplication>

#include "client.hpp"
#include "main_window.hpp"

class Controller : QObject{
  Q_OBJECT

  public:

    /* Constructeur de la class dans laquel le lien entre les signaux et les
       slots des class Client et MainWindow sont établis.
     */
    Controller(Client *c, MainWindow *w);
    ~Controller();
  
  public slots:

    /* Fonction de callback permettant la récupération du message à envoyer
     * depuis la classe MainWindow. L'appel à la méthode d'envoi de message de
     * la classe client est ensuite effectuer avec les informations récupérées.
     */
    void SendMessage();

  private:
    Client *client;
    MainWindow *main_window;
};


#endif
