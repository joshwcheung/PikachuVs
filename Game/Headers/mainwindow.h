#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameboard.h"
#include "gameoverwidget.h"
#include "howto.h"
#include "quitwidget.h"
#include <QDesktopWidget>
#include <QFont>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QRect>
#include <QVBoxLayout>

class GameBoard;
class GameOverWidget;
class HowTo;

/**
 * @brief The MainWindow class displays the main menu for the game\n
 * @GameBoard* board points to the GameBoard\n
 * @HowTo* how points to the HowTo\n
 * @QuitWidget* quit points to the QuitWidget\n
 * @QLabel* title displays the title of the game\n
 * @QPushButton* play takes the user to the game board\n
 * @QPushButton* howto takes the user to the HowTo screen\n
 * @QPushButton* exit brings up the QuitWidget\n
 * @QVBoxLayout* buttons stores the layout for the QPushButton objects\n
 * @QVBoxLayout* final_layout stores the final layout\n
 * @QWidget* central is the central widget applying final_layout
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief closeEvent shows QuitWidget when attempting to close
     * @param e unused
     */

    void closeEvent(QCloseEvent* e);

    /**
     * @brief setGameBoard sets GameBoard
     * @param game_board the GameBoard input
     */

    //void setGameBoard(GameBoard* game_board);

    /**
     * @brief setHowTo sets HowTo
     * @param how_to the HowTo input
     */

    void setHowTo(HowTo* how_to);

    /**
     * @brief setQuitWidget sets QuitWidget
     * @param quit_widget the QuitWidget input
     */

    void setQuitWidget(QuitWidget* quit_widget);

    /**
     * @brief setGameOverWidget sets GameOverWidget
     * @param game_over the GameOverWidget input
     */

    void setGameOverWidget(GameOverWidget* game_over);

public slots:

    /**
     * @brief makeGameBoard makes a new GameBoard
     */

    void makeGameBoard();

private:

    //Title label
    QLabel* title;

    //Buttons
    QPushButton* play;
    QPushButton* howto;
    QPushButton* exit;

    //Layouts
    QVBoxLayout* buttons;
    QVBoxLayout* final_layout;

    //Central widget
    QWidget* central;

    //Widgets
    GameBoard* board;
    HowTo* how;
    QuitWidget* quit;
    GameOverWidget* over;
};

#endif // MAINWINDOW_H
