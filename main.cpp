#include <QApplication>
#include <QtGui>
#include "main_window.hpp"
#include "client.hpp"
#include "controller.hpp"

int main(int argc, char* argv[]){/*astantier les modules et lancer l'app*/
  
  // Récupération des arguments
  if (argc != 4){
    qDebug() << "Usage: " << argv[0] << " username server port";
    return -1;
  }
  QString username(argv[1]);
  QString server(argv[2]);
  int port = QString(argv[3]).toInt();
  
  // Mise en place de l'application
  QApplication app(argc, argv); /*l'objet app permet d'instantier la boucle evenmetielle*/
  MainWindow window;
  Client client(username, server, port);/*je crée le client*: gère tout ce qui est affichage*/
  Controller controller(&client, &window);
  
  // Lancement de la boucle événementielle.
  return app.exec(); 
}
