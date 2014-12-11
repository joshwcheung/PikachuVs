#include "..\Headers\gameoverwidget.h"

GameOverWidget::GameOverWidget(QWidget *parent) :
    QWidget(parent)
{
    //Create confirmation message and buttons
    over = new QLabel("Game Over!");
    playAgain = new QPushButton("Play Again");
    mainMenu = new QPushButton("Menu");
    exit = new QPushButton("Exit");

    //Add widgets to layouts
    QVBoxLayout* buttons = new QVBoxLayout;
    buttons->addWidget(playAgain);
    buttons->addWidget(mainMenu);
    buttons->addWidget(exit);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(over);
    layout->addLayout(buttons);

    this->setLayout(layout);

    //clicking playAgain creates new GameBoard
    QObject::connect(playAgain, SIGNAL(clicked()), this, SLOT(makeGameBoard()));

}

void GameOverWidget::closeEvent(QCloseEvent *e) {
    e->ignore();

    //Attempting to exit brings up QuitWidget
    quit->show();
}

void GameOverWidget::setMainWindow(MainWindow* main_window) {
    mw = main_window;
    //clicking mainMenu takes user to MainWindow
    QObject::connect(mainMenu, SIGNAL(clicked()), this, SLOT(goToMenu()));
}

void GameOverWidget::setGameBoard(GameBoard* game_board) {
    board = game_board;
}

void GameOverWidget::setQuitWidget(QuitWidget* quit_widget) {
    quit = quit_widget;
    //clicking exit takes user to QuitWidget
    QObject::connect(exit, SIGNAL(clicked()), quit, SLOT(show()));
}

void GameOverWidget::makeGameBoard() {
    //Clicking "Play Again" creates a new game board, deletes the old game board, and hides GameOverWidget
    delete board;
    board = new GameBoard;
    board->setMainWindow(mw);
    board->setQuitWidget(quit);
    board->setGameOverWidget(this);
    this->setGameBoard(board);
    QDesktopWidget desktop;
    QRect screen = desktop.availableGeometry();
    board->setFixedSize(screen.width() - 14, screen.height() - 36);
    board->show();
    this->hide();
}

void GameOverWidget::goToMenu() {
    //delete GameBoard, show MainWindow, hide GameOverWidget
    delete board;
    mw->show();
    this->hide();
}

GameOverWidget::~GameOverWidget() {
}
