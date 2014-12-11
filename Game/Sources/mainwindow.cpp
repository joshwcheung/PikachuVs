#include "..\Headers\mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create Title label
    title = new QLabel;
    title->setPixmap(QPixmap(QString("../Images/Title.png")));

    //Create Buttons
    play = new QPushButton("Play");
    howto = new QPushButton("How to Play");
    exit = new QPushButton("Exit");

    //title->setStyleSheet("QLabel { color : white }");

    //play->setStyleSheet("QPushButton { color : white }");
    //howto->setStyleSheet("QPushButton { color : white }");
    //exit->setStyleSheet("QPushButton { color : white }");

    //Format labels and buttons
    QFont font = title->font();
    font.setPointSize(50);
    font.setBold(true);
    title->setFont(font);
    font.setPointSize(40);
    play->setFont(font);
    howto->setFont(font);
    exit->setFont(font);

    //Place all widgets in a column
    buttons = new QVBoxLayout;
    buttons->addWidget(play, 0, Qt::AlignCenter);
    buttons->addWidget(howto, 0, Qt::AlignCenter);
    buttons->addWidget(exit, 0, Qt::AlignCenter);

    final_layout = new QVBoxLayout;
    final_layout->addWidget(title, 0, Qt::AlignCenter);
    final_layout->addLayout(buttons);

    //Add to central widget
    central = new QWidget;
    central->setLayout(final_layout);
    this->setCentralWidget(central);

    //Adjust size of window according to desktop
    QDesktopWidget desktop;
    QRect screen = desktop.availableGeometry();
    setFixedSize(screen.width() - 14, screen.height() - 36);

    //Set background color of MainWindow to black
    //setStyleSheet("background-color : black");

    //Set Window Title to "Title"
    setWindowTitle("Title");

    QObject::connect(play, SIGNAL(clicked()), this, SLOT(makeGameBoard()));
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent *e) {
    e->ignore();
    //this->hide();

    //Attempting to exit brings up QuitWidget
    quit->show();
}

void MainWindow::setHowTo(HowTo* how_to) {
    how = how_to;

    //Clicking "How to Play" brings up HowTo
    QObject::connect(howto, SIGNAL(clicked()), how, SLOT(show()));
}

void MainWindow::setQuitWidget(QuitWidget* quit_widget) {
    quit = quit_widget;

    //Clicking "Exit" brings up QuitWidget
    QObject::connect(exit, SIGNAL(clicked()), quit, SLOT(show()));
}

void MainWindow::setGameOverWidget(GameOverWidget* game_over) {
    over = game_over;
    over->setMainWindow(this);
    over->setQuitWidget(quit);
}

void MainWindow::makeGameBoard() {
    //Clicking "Play" creates a new game board and hides main menu
    board = new GameBoard;
    board->setMainWindow(this);
    board->setQuitWidget(quit);
    board->setGameOverWidget(over);
    over->setGameBoard(board);
    QDesktopWidget desktop;
    QRect screen = desktop.availableGeometry();
    board->setFixedSize(screen.width() - 14, screen.height() - 36);
    board->show();
    this->hide();
}
