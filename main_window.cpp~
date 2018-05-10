#include "main_window.hpp"


MainWindow::MainWindow(){
  CreateLayouts();
  CreateMainArea();
  CreateButtons();
  show();
}

void MainWindow::CreateLayouts(){
  main_layout = new QVBoxLayout;
  central_widget = new QWidget;
  central_widget->setLayout(main_layout);
  setCentralWidget(central_widget);
}

void MainWindow::CreateMainArea(){
  display_chat = new QTextEdit;
  display_chat->setReadOnly(true);

  user_input = new QLineEdit;
  
  main_layout->addWidget(display_chat);
  main_layout->addWidget(user_input);
}

void MainWindow::CreateButtons(){
  send_btn = new QPushButton("Envoyer");
  disconnect_btn = new QPushButton("Deconnexion");

  QHBoxLayout *layout = new QHBoxLayout;

  layout->addWidget(disconnect_btn);
  layout->addWidget(send_btn);

  main_layout->addLayout(layout);
}

void MainWindow::UpdateChat(QString msg){
  display_chat->setPlainText(display_chat->toPlainText() + msg +"\n");
}
