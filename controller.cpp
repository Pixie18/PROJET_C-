#include "controller.hpp"

Controller::Controller(Client *c, MainWindow *w){/*connecter les diff signaux au callback*/
  client = c;
  main_window = w;

  QObject::connect(main_window->getDisconnectBtn(), SIGNAL(clicked()), client, /*lorsqu le boutton disconnect est cliquer je fas niania...*/ 
      SLOT(Disconnect()));
  QObject::connect(main_window->getSendBtn(), SIGNAL(clicked()), this,
      SLOT(SendMessage()));
  QObject::connect(client, SIGNAL(newMessage(QString)), main_window,
      SLOT(UpdateChat(QString)));

}

Controller::~Controller(){
}

void Controller::SendMessage(){/*permet a prtir du controllet de récup le msg entré par le user et appler la methd send */
  client->SendMessage(main_window->getUserInput()->text());
  main_window->getUserInput()->setText("");/*j'efface la zone pour que le user puisse rentrer un mv msg */ 
}
