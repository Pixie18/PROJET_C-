#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QApplication>
#include <QtGui>
#include <vector>

using namespace std;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    /* Le constructeur de la classe est utilisé pour construire les différents
     * éléments constituant la fenêtre.
     */
    MainWindow();

    /* Fonction de création des éléments de la fenêtre.
     */
    void CreateLayouts();
    void CreateMainArea(); 
    void CreateButtons();

    /* Getters pour les éléments des la fenêtre susceptible de générer des
     * signaux utiles.
     */
    QPushButton* getDisconnectBtn(){return disconnect_btn;};
    QPushButton* getSendBtn(){return send_btn;};
    QLineEdit* getUserInput(){return user_input;};
  
  public slots:

    /* Fonction de callback permettant la mise à jour de la zone d'affichage du
     *  chat.
     */
    void UpdateChat(QString msg);

  private: 
    // Boutons
    QPushButton *send_btn;
    QPushButton *disconnect_btn;

    // Conteneur de placement.
    QVBoxLayout *main_layout;
    
    // Zones de texte.
    QTextEdit *display_chat;
    QLineEdit *user_input;
    
    // Conteneur graphique principal.
    QWidget *central_widget;


};
#endif
