#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include "gameboard.h"
#include "mainwindow.h"
#include "quitwidget.h"
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <QWidget>

class GameBoard;
class MainWindow;

/**
 * @brief The GameOverWidget class\n
 * @Qlabel* over displays the "Game Over!" message\n
 * @QPushButton* playAgain takes the user to a new game\n
 * @QPushButton* mainMenu takes the user to the main menu\n
 * @QPushButton* exit brings up the QuitWidget\n
 * @MainWindow* mw points to the MainWindow\n
 * @GameBoard* board points to the GameBoard\n
 * @QuitWidget* quit points to the QuitWidget
 */

class GameOverWidget : public QWidget
{
    Q_OBJECT

public:

    explicit GameOverWidget(QWidget *parent = 0);
    ~GameOverWidget();

    /**
     * @brief closeEvent opens the QuitWidget
     * @param e unused
     */

    void closeEvent(QCloseEvent* e);

    /**
     * @brief setMainWindow sets MainWindow
     * @param main_window the MainWindow input
     */

    void setMainWindow(MainWindow* main_window);

    /**
     * @brief setGameBoard sets GameBoard
     * @param game_board the GameBoard input
     */

    void setGameBoard(GameBoard* game_board);

    /**
     * @brief setQuitWidget sets QuitWidget
     * @param quit_widget the QuitWidget input
     */

    void setQuitWidget(QuitWidget* quit_widget);

public slots:

    /**
     * @brief makeGameBoard makes a new GameBoard
     */

    void makeGameBoard();

    /**
     * @brief goToMenu takes the user to the main menu
     */

    void goToMenu();

private:

    //Message
    QLabel* over;

    //Buttons
    QPushButton* playAgain;
    QPushButton* mainMenu;
    QPushButton* exit;

    //Widgets
    MainWindow* mw;
    GameBoard* board;
    QuitWidget* quit;

};

#endif // GAMEOVERWIDGET_H
