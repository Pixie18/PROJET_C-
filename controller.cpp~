#include "controller.hpp"

Controller::Controller(Client *c, MainWindow *w){
  client = c;
  main_window = w;

  QObject::connect(main_window->getDisconnectBtn(), SIGNAL(clicked()), client,
      SLOT(Disconnect()));
  QObject::connect(main_window->getSendBtn(), SIGNAL(clicked()), this,
      SLOT(SendMessage()));
  QObject::connect(client, SIGNAL(newMessage(QString)), main_window,
      SLOT(UpdateChat(QString)));

}

Controller::~Controller(){
}

void Controller::SendMessage(){
  client->SendMessage(main_window->getUserInput()->text());
  main_window->getUserInput()->setText("");
}
