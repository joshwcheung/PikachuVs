/**Joshua Cheung
 * PIC 10C
 * Discussion 1A
 * 12/10/14
 * A tile-based game in which the objective is to defeat a number of enemies
  */

#include "..\Headers\mainwindow.h"
#include "..\Headers\quitwidget.h"
#include "..\Headers\gameboard.h"
#include "..\Headers\howto.h"
#include "..\Headers\gameoverwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Create components
    MainWindow* w = new MainWindow;
    HowTo* h = new HowTo;
    QuitWidget* q = new QuitWidget;
    GameOverWidget* g = new GameOverWidget;

    w->setHowTo(h);
    w->setQuitWidget(q);
    w->setGameOverWidget(g);

    w->show();

    //Clicking "OK" on QuitWidget closes the application
    QObject::connect(q->ok, SIGNAL(clicked()), &a, SLOT(quit()));

    return a.exec();
}
