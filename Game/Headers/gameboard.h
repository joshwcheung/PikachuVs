#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gameoverwidget.h"
#include "mainwindow.h"
#include "pikachu.h"
#include "quitwidget.h"
#include <QCoreApplication>
#include <QCursor>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QString>
#include <QWidget>
#include <QTimer>
#include <chrono>
#include <cmath>
#include <random>
#include <thread>
#include <vector>

class GameOverWidget;
class MainWindow;

/**
 * @brief The GameBoard class displays the board on which the game is played\n
 * @QWidget* Top displays the lives and score\n
 * @QLabel** lives stores pointers to QLabel objects displaying the images for each life\n
 * @QLabel* score_label displays the score\n
 * @unsigned int score stores the score\n
 * @QWidget* Board displays the tiles\n
 * @QLabel** labels stores pointers to QLabel objects displaying each tile\n
 * @int board_size stores the size of the board\n
 * @QPoint cursor_location stores the location of the cursor\n
 * @QPoint life_position stores the location of the extra life\n
 * @bool clicked stores whether the mouse was clicked\n
 * @QPixmap* squirtle_image stores the image of the squirtles\n
 * @QPixmap* charmander_image stores the image of the charmanders\n
 * @QPixmap* attack_image stores the image of the attack\n
 * @size_t number_squirtles stores the total number of squirtles on the board\n
 * @size_t alive_squirtles stores the number of squirtles that have yet to be defeated\n
 * @size_t number_charmanders stores the total number of charmanders on the board\n
 * @size_t alive_charmanders stores the number of charmanders that have yet to be defeated\n
 * @size_t enemies_on_board stores the number of enemies on board (10 max)\n
 * @QuitWidget* q points to the QuitWidget object\n
 * @MainWindow* m points to the MainWindow object\n
 * @GameOverWidget* g points to the GameOverWidget object\n
 * @Pikachu* pika points to the Pikachu object controlled by the player
*/

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

    /**
     * @brief keyPressEvent determines what happens when the keyboard is pressed
     * @param event is the default event that occurs when the keyboard is pressed
     */

    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief paintEvent repaints the game
     * @param e unused
     */

    void paintEvent(QPaintEvent *e);

    /**
     * @brief closeEvent returns user to main menu when attempting to close
     * @param e unused
     */

    void closeEvent(QCloseEvent *e);

    /**
     * @brief setQuitWidget sets QuitWidget
     * @param quit_widget the QuitWidget input
     */

    void setQuitWidget(QuitWidget* quit_widget);

    /**
     * @brief setMainWindow sets MainWindow
     * @param main_window the MainWindow input
     */

    void setMainWindow(MainWindow* main_window);

    /**
     * @brief setGameOverWidget sets GameOverWidget
     * @param game_over the GameOverWidget input
     */

    void setGameOverWidget(GameOverWidget* game_over);

    /**
     * @brief squirtleAvailable determines if a squirtle is available for spawning
     * @return true if a squirtle is available
     */

    bool squirtleAvailable();

    /**
     * @brief charmanderAvailable determines if a charmander is available for spawning
     * @return true if a charmander if available
     */

    bool charmanderAvailable();

    /**
     * @brief positionAvailableForSpawn determines if a squirtle can be spawned at target location
     * @param x the target x value
     * @param y the target y value
     * @return true if space is unoccupied
     */

    bool positionAvailableForSpawn(int x, int y);

    /**
     * @brief validEnemyMove
     * @param x the target x value
     * @param y the target y value
     * @return  true if space is unoccupied
     */

    bool validEnemyMove(int x, int y);

    /**
     * @brief defeated determines if Pikachu is defeated
     * @return true if Pikachu shares space with an enemy
     */

    bool defeated();

    /**
     * @brief gameOver determines if the player loses
     * @return true if all lives are gone
     */

    bool gameOver();

public slots:

    /**
     * @brief updateSquirtles updates the squirtles on the board
     */

    void updateSquirtles();

    /**
     * @brief updateCharmanders updates the charmanders on the board
     */

    void updateCharmanders();

    /**
     * @brief displayLife puts extra life on board if current lives < max lives and score >= 30
     */

    void displayLife();

    /**
     * @brief clearAttack clears attack image
     */

    void clearAttack();

signals:

    /**
     * @brief mouseAbove emitted when mouse is above Pikachu
     */

    void mouseAbove();

    /**
     * @brief mouseBelow emitted when mouse is below Pikachu
     */

    void mouseBelow();

    /**
     * @brief mouseToLeft emitted when mouse is left of Pikachu
     */

    void mouseToLeft();

    /**
     * @brief mouseToRight emitted when mouse is right of Pikachu
     */

    void mouseToRight();

private:

    // Top Bar Variables
    QWidget* Top;
    QLabel** lives;
    QLabel* score_label;
    unsigned int score;

    //Board Variables
    QWidget* Board;
    QLabel** labels;
    int board_size;
    QPoint cursor_location;
    QPoint life_position;
    bool clicked;

    //Images
    QPixmap* squirtle_image;
    QPixmap* charmander_image;
    QPixmap* attack_image;

    //Enemy info
    QPoint *squirtle_positions;
    size_t number_squirtles;
    size_t alive_squirtles;
    QPoint *charmander_positions;
    size_t number_charmanders;
    size_t alive_charmanders;
    size_t enemies_on_board;

    //Widgets
    QuitWidget* q;
    MainWindow* m;
    GameOverWidget* g;

    //Pikachu
    Pikachu* pika;
};

#endif // GAMEBOARD_H
