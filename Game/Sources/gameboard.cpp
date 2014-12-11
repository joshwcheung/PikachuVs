#include "..\Headers\gameboard.h"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{
    //Create top bar
    Top = new QWidget;
    QHBoxLayout* top_bar = new QHBoxLayout(Top);

    QString lives_filename = "../Images/Lives.png";

    //Create Pikachu
    pika = new Pikachu;

    //Create life labels
    lives = new QLabel*[pika->get_lives() - 1];

    for(size_t i = 0; i < pika->get_lives() - 1; i++) {
        lives[i] = new QLabel;
        lives[i]->setPixmap(QPixmap(lives_filename));
        lives[i]->setFixedSize(50, 50);
        lives[i]->setScaledContents(true);
        top_bar->addWidget(lives[i]);
    }

    QSpacerItem* horizontal_space = new QSpacerItem(420, 10);
    top_bar->addSpacerItem(horizontal_space);

    //Create score label
    score = 0;
    score_label = new QLabel("Score: " + QString::number(score));

    //Format label
    QFont font = score_label->font();
    font.setPointSize(40);
    font.setBold(true);
    score_label->setFont(font);

    top_bar->addWidget(score_label);

    //Create board
    Board = new QWidget;

    //Tentatively 15x15
    board_size = 15;
    labels = new QLabel*[board_size * board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    for(int i = 0; i < board_size; i++) {
        for(int j = 0; j < board_size; j++) {
            labels[i * board_size + j] = new QLabel;
            labels[i * board_size + j]->setFixedSize(50, 50);
            labels[i * board_size + j]->setStyleSheet("QLabel { background-color : black; color : white; }");
            labels[i * board_size + j]->setFrameStyle(1);
            labels[i * board_size + j]->setAlignment(Qt::AlignCenter);
            SquareGrid -> addWidget(labels[i * board_size + j] , i, j);
        }
    }

    //Set Pikachu location
    labels[pika->get_y() * board_size + pika->get_x()]->setPixmap(*(pika->get_up_image()));
    labels[pika->get_y() * board_size + pika->get_x()]->setScaledContents(true);

    //Create a vertical box layout for top bar and board
    QVBoxLayout* all = new QVBoxLayout;

    all->addWidget(Top, 0, Qt::AlignCenter);
    all->addWidget(Board, 0, Qt::AlignCenter);

    this->setLayout(all);

    //Prevent resizing
    setFixedSize(1000, 800);

    //Create enemies and have them move around board
    //(-1, -1) means that enemy is available for spawning
    //(board_size, board_size) means that enemy is defeated
    //squirtles can only move horizontally
    //charmanders chase you
    squirtle_image = new QPixmap(QString("../Images/Squirtle.png"));
    charmander_image = new QPixmap(QString("../Images/Charmander.png"));
    attack_image = new QPixmap(QString("../Images/Attack.png"));

    number_squirtles = 25;
    alive_squirtles = number_squirtles;
    squirtle_positions = new QPoint[number_squirtles];

    for (size_t i = 0; i < number_squirtles; i++) {
        squirtle_positions[i].setX(-1);
        squirtle_positions[i].setY(-1);
    }

    number_charmanders = 25;
    alive_charmanders = number_charmanders;
    charmander_positions = new QPoint[number_charmanders];

    for (size_t i = 0; i < number_charmanders; i++) {
        charmander_positions[i].setX(-1);
        charmander_positions[i].setY(-1);
    }

    //no enemies on board
    enemies_on_board = 0;

    //extra life
    life_position.setX(-1);
    life_position.setY(-1);

    QTimer* STimer = new QTimer(this);
    QTimer* CTimer = new QTimer(this);
    QTimer* LTimer = new QTimer(this);

    connect(STimer, SIGNAL(timeout()), this, SLOT(updateSquirtles()));
    connect(CTimer, SIGNAL(timeout()), this, SLOT(updateCharmanders()));
    connect(LTimer, SIGNAL(timeout()), this, SLOT(displayLife()));
    //clear attack images every second
    connect(LTimer, SIGNAL(timeout()), this, SLOT(clearAttack()));

    STimer->start(750);
    CTimer->start(500);
    LTimer->start(1000);
}

void GameBoard::keyPressEvent(QKeyEvent *event) {
    int x = pika->get_x();
    int y = pika->get_y();

    //W = up, A = left, S = down, D = right
    switch (event->key()) {
    case Qt::Key_A:
        pika->set_dir(0);
        if(pika->get_x() != 0)
            pika->set_x(x - 1);
        break;

    case Qt::Key_D:
        pika->set_dir(0);
        if(pika->get_x() != board_size - 1)
            pika->set_x(x + 1);
        break;

    case Qt::Key_W:
        pika->set_dir(0);
        if(pika->get_y() != 0)
            pika->set_y(y - 1);
        break;

    case Qt::Key_S:
        pika->set_dir(0);
        if(pika->get_y() != board_size - 1)
            pika->set_y(y + 1);
        break;

    case Qt::Key_Up:
        pika->set_dir(0);
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == x && squirtley == y - 1) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
                ++score;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == x && charmandery == y - 1) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
                ++score;
            }
        }
        if(pika->get_y() != 0)
            labels[(pika->get_y() - 1) * board_size + pika->get_x()]->setPixmap(*attack_image);
        break;

    case Qt::Key_Down:
        pika->set_dir(1);
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == x && squirtley == y + 1) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
                ++score;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == x && charmandery == y + 1) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
                ++score;
            }
        }
        if(pika->get_y() != board_size - 1)
            labels[(pika->get_y() + 1) * board_size + pika->get_x()]->setPixmap(*attack_image);
        break;

    case Qt::Key_Left:
        pika->set_dir(2);
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == x - 1 && squirtley == y) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
                ++score;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == x - 1 && charmandery == y) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
                ++score;
            }
        }
        if(pika->get_x() != 0)
            labels[pika->get_y() * board_size + pika->get_x() - 1]->setPixmap(*attack_image);
        break;

    case Qt::Key_Right:
        pika->set_dir(3);
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == x + 1 && squirtley == y) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
                ++score;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == x + 1 && charmandery == y) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
                ++score;
            }
        }
        if(pika->get_x() != board_size - 1)
            labels[pika->get_y() * board_size + pika->get_x() + 1]->setPixmap(*attack_image);
        break;

    default:
        QWidget::keyPressEvent(event);
    }

    //Check if life is lost
    if(defeated()) {
        if(pika->get_lives() > 1) {
            lives[pika->get_lives() - 2]->clear();
            pika->lose_life();
        }
        else if(pika->get_lives() == 1)
            pika->lose_life();
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == pika->get_x() && squirtley == pika->get_y()) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == pika->get_x() && charmandery == pika->get_y()) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
            }
        }
    }

    //Check if extra life collected
    if(life_position.rx() == pika->get_x() && life_position.ry() == pika->get_y()) {
        labels[life_position.ry() * board_size + life_position.rx()]->clear();
        life_position.setX(board_size);
        life_position.setY(board_size);
        pika->gain_life();
        lives[0]->setPixmap(QPixmap("../Images/Lives.png"));
    }

    //Check if game is over
    if(gameOver())
        g->show();

    //Check if game is won
    if(alive_squirtles == 0 && alive_charmanders == 0)
        g->show();

    QCoreApplication::processEvents();
    repaint();

    if (!gameOver() && (alive_squirtles > 0 || alive_charmanders > 0))
        labels[y * board_size + x]->clear();
    return;
}

void GameBoard::paintEvent(QPaintEvent *e) {
    e->ignore();
    int px = pika->get_x();
    int py = pika->get_y();

    //Draw pikachu as long as game isn't over
    if(!gameOver() && (alive_squirtles > 0 || alive_charmanders > 0)) {
        switch(pika->get_dir()) {
        case 0:
            labels[py * board_size + px]->setPixmap(*(pika->get_up_image()));
            break;

        case 1:
            labels[py * board_size + px]->setPixmap(*(pika->get_down_image()));
            break;

        case 2:
            labels[py * board_size + px]->setPixmap(*(pika->get_left_image()));
            break;

        case 3:
            labels[py * board_size + px]->setPixmap(*(pika->get_right_image()));
            break;
        }

        labels[py * board_size + px]->setScaledContents(true);
    }

    //Draw squirtles, leave running even when game is over for aesthetic reasons
    for(size_t i = 0; i < number_squirtles; i++) {
        int sx = squirtle_positions[i].rx();
        int sy = squirtle_positions[i].ry();

        if(sx >= 0 && sy >= 0 && sx < board_size && sy < board_size) {
            labels[sy * board_size + sx]->setPixmap(*squirtle_image);
            labels[sy * board_size + sx]->setScaledContents(true);
        }
    }

    //Draw charmanders, leave running even when game is over for aesthetic reasons
    for(size_t i = 0; i < number_charmanders; i++) {
        int cx = charmander_positions[i].rx();
        int cy = charmander_positions[i].ry();

        if(cx >= 0 && cy >= 0 && cx < board_size && cy < board_size) {
            labels[cy * board_size + cx]->setPixmap(*charmander_image);
            labels[cy * board_size + cx]->setScaledContents(true);
        }
    }

    //Draw extra life
    int lx = life_position.rx();
    int ly = life_position.ry();
    if (lx >= 0 && ly >= 0 && lx < board_size && ly < board_size) {
        labels[ly * board_size + lx]->setPixmap(QPixmap("../Images/Lives.png"));
        labels[ly * board_size + lx]->setScaledContents(true);
    }

    //Update score counter
    score_label->setText("Score: " + QString::number(score));
}

void GameBoard::closeEvent(QCloseEvent *e) {
    //Show main menu
    e->ignore();
    m->show();

    //Delete GameBoard so that pressing "Play" in MainWindow starts a new game
    delete this;
}

void GameBoard::setQuitWidget(QuitWidget* quit_widget) {
    q = quit_widget;
}

void GameBoard::setMainWindow(MainWindow* main_window) {
    m = main_window;
}

void GameBoard::setGameOverWidget(GameOverWidget *game_over) {
    g = game_over;
}

bool GameBoard::squirtleAvailable() {
    //available means position is (-1, 1)
    for(size_t i = 0; i < number_squirtles; i++)
        if (squirtle_positions[i].rx() == -1 && squirtle_positions[i].ry() == -1)
            return true;
    return false;
}

bool GameBoard::charmanderAvailable() {
    //available means position is (-1, 1)
    for(size_t i = 0; i < number_charmanders; i++)
        if (charmander_positions[i].rx() == -1 && charmander_positions[i].ry() == -1)
            return true;
    return false;
}

bool GameBoard::positionAvailableForSpawn(int x, int y) {
    //don't spawn on top of Pikachu
    if (x == pika->get_x() && y == pika->get_y())
        return false;
    //don't spawn on top of squirtles
    for(size_t i = 0; i < number_squirtles; i++) {
        if (x == squirtle_positions[i].rx() && y == squirtle_positions[i].ry())
            return false;
    }
    //don't spawn on top of charmanders
    for(size_t i = 0; i < number_charmanders; i++) {
        if (x == charmander_positions[i].rx() && y == charmander_positions[i].ry())
            return false;
    }
    //don't spawn on top of extra life
    if (x == life_position.rx() && y == life_position.ry())
        return false;
    //don't spawn outside of board
    if (x < 0 || x >= board_size || y < 0 || y >= board_size)
        return false;
    return true;
}

bool GameBoard::validEnemyMove(int x, int y) {
    //don't run into other enemies
    for(size_t i = 0; i < number_squirtles; i++) {
        if (x == squirtle_positions[i].rx() && y == squirtle_positions[i].ry())
            return false;
    }
    for(size_t i = 0; i < number_charmanders; i++) {
        if (x == charmander_positions[i].rx() && y == charmander_positions[i].ry())
            return false;
    }
    //don't run on top of extra life
    if (x == life_position.rx() && y == life_position.ry())
        return false;
    //don't move outside of board
    if (x < 0 || x >= board_size || y < 0 || y >= board_size)
        return false;
    return true;
}

bool GameBoard::defeated() {
    //check if Pikachu is hit by an enemy
    for(size_t i = 0; i < number_squirtles; i++) {
        if(pika->get_x() == squirtle_positions[i].rx() && pika->get_y() == squirtle_positions[i].ry())
            return true;
    }
    for(size_t i = 0; i < number_charmanders; i++) {
        if(pika->get_x() == charmander_positions[i].rx() && pika->get_y() == charmander_positions[i].ry())
            return true;
    }
    return false;
}

bool GameBoard::gameOver() {
    //game is over if Pikachu has 0 lives
    if (pika->get_lives() == 0)
        return true;
    else
        return false;
}

void GameBoard::updateSquirtles() {
    //randomly decide if squirtle moves left or right (0 = left, 1 = right)
    std::uniform_int_distribution<int> left_or_right(0, 1);
    for(size_t i = 0; i < number_squirtles; i++) {
        int px = squirtle_positions[i].rx();
        int py = squirtle_positions[i].ry();

        if(px >= 0 && py >= 0 && px < board_size && py < board_size)
            labels[py * board_size + px]->clear();

        int nx = px;
        if (left_or_right(generator) == 0)
            nx--;
        else
            nx++;

        //don't move if move is not valid
        if(validEnemyMove(nx, py))
            squirtle_positions[i].setX(nx);
    }

    std::uniform_real_distribution<double> spawner(0, 1);
    std::uniform_int_distribution<int> positioner(0, board_size - 1);

    //if squirtles are available for spawning and less than 10 enemies (to prevent crowding of board), 50% chance to spawn
    if (squirtleAvailable() && enemies_on_board < 10) {
        if (spawner(generator) < 0.5) {
            for(size_t i = 0; i < number_squirtles; i++) {
                int px = squirtle_positions[i].rx();
                int py = squirtle_positions[i].ry();
                if(px == -1 && py == -1) {
                    int nx = positioner(generator);
                    int ny = positioner(generator);
                    if(positionAvailableForSpawn(nx, ny)) {
                        squirtle_positions[i].setX(nx);
                        squirtle_positions[i].setY(ny);
                        ++enemies_on_board;
                    }
                    break;
                }
            }
        }
    }

    //check if life is lost
    if(defeated()) {
        if(pika->get_lives() > 1) {
            lives[pika->get_lives() - 2]->clear();
            pika->lose_life();
        }
        else if(pika->get_lives() == 1)
            pika->lose_life();
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == pika->get_x() && squirtley == pika->get_y()) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == pika->get_x() && charmandery == pika->get_y()) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
            }
        }
    }

    //check if game is over
    if(gameOver())
        g->show();

    QCoreApplication::processEvents();
    repaint();
}

void GameBoard::updateCharmanders() {
    //randomly decide if charmander chases you (0, 1, 2 = yes, 3 = no (75% it chases you))
    //if charmander does not chase, move in random position (0 = up, 1 = down, 2 = left, 3 = right)
    std::uniform_int_distribution<int> chases(0, 3);
    for(size_t i = 0; i < number_charmanders; i++) {
        int px = charmander_positions[i].rx();
        int py = charmander_positions[i].ry();

        if(px >= 0 && py >= 0 && px < board_size && py < board_size)
            labels[py * board_size + px]->clear();

        int nx = px;
        int ny = py;
        if (chases(generator) < 2) {
            //gets closer to you: if it is further away horizontally; otherwise, move vertically
            //if same in both orientations, then move randomly (0, 1 = horizontal, 2, 3 = vertical)
            //ex. pika @ (5, 5); char @ (7, 6) -> move 1 left
            //ex. pika @ (5, 5); char @ (6, 6) -> move 1 left or 1 up randomly
            if(abs(px - pika->get_x()) > abs(py - pika->get_y())) { //further away horizontally
                if (px < pika->get_x())
                    nx++;
                else
                    nx--;
            }
            else if (abs(px - pika->get_x()) < abs(py - pika->get_y())) { //further away vertically
                if (py < pika->get_y())
                    ny++;
                else
                    ny--;
            }
            else if (abs(px - pika->get_x()) == abs(py - pika->get_y())) { //same distance away horizontally/vertically
                int hor_vert = chases(generator);
                if (hor_vert < 2) { //move horizontally
                    if (px < pika->get_x())
                        nx++;
                    else
                        nx--;
                }
                else {  //move vertically
                    if (py < pika->get_y())
                        ny++;
                    else
                        ny--;
                }
            }
        }
        else {
            int direction = chases(generator);
            switch(direction) {
            case 0: //move up
                ny--;
                break;
            case 1: //move down
                ny++;
                break;
            case 2: //move left
                nx--;
                break;
            case 3: //move right
                nx++;
                break;
            }
        }

        //don't move if move is not valid
        if(validEnemyMove(nx, ny)) {
            charmander_positions[i].setX(nx);
            charmander_positions[i].setY(ny);
        }
    }

    std::uniform_real_distribution<double> spawner(0, 1);
    std::uniform_int_distribution<int> positioner(0, board_size - 1);

    //if charmanders are available for spawning and less than 10 enemies (to prevent crowding of board), 50% chance to spawn
    if (charmanderAvailable() && enemies_on_board < 10) {
        if (spawner(generator) < 0.5) {
            for(size_t i = 0; i < number_charmanders; i++) {
                int px = charmander_positions[i].rx();
                int py = charmander_positions[i].ry();
                if(px == -1 && py == -1) {
                    int nx = positioner(generator);
                    int ny = positioner(generator);
                    if(positionAvailableForSpawn(nx, ny)) {
                        charmander_positions[i].setX(nx);
                        charmander_positions[i].setY(ny);
                        ++enemies_on_board;
                    }
                    break;
                }
            }
        }
    }

    //check if life is lost
    if(defeated()) {
        if(pika->get_lives() > 1) {
            lives[pika->get_lives() - 2]->clear();
            pika->lose_life();
        }
        else if(pika->get_lives() == 1)
            pika->lose_life();
        for(int i = 0, j = number_squirtles; i < j; i++) {
            int squirtlex = squirtle_positions[i].rx();
            int squirtley = squirtle_positions[i].ry();
            if(squirtlex == pika->get_x() && squirtley == pika->get_y()) {
                labels[squirtley * board_size + squirtlex]->clear();
                squirtle_positions[i].setX(board_size);
                squirtle_positions[i].setY(board_size);
                --alive_squirtles;
                --enemies_on_board;
            }
        }
        for(int i = 0, j = number_charmanders; i < j; i++) {
            int charmanderx = charmander_positions[i].rx();
            int charmandery = charmander_positions[i].ry();
            if(charmanderx == pika->get_x() && charmandery == pika->get_y()) {
                labels[charmandery * board_size + charmanderx]->clear();
                charmander_positions[i].setX(board_size);
                charmander_positions[i].setY(board_size);
                --alive_charmanders;
                --enemies_on_board;
            }
        }
    }

    //check if game is over
    if(gameOver())
        g->show();

    QCoreApplication::processEvents();
    repaint();
}

void GameBoard::displayLife() {
    if (pika->get_lives() == 1 && score >= 30 && life_position.rx() == -1 && life_position.ry() == -1) {
        //5% chance to have life show on board
        std::uniform_real_distribution<double> spawner(0, 1);
        if (spawner(generator) > 0.95) {
            std::uniform_int_distribution<int> positioner(0, board_size);
            int x = positioner(generator);
            int y = positioner(generator);
            if (positionAvailableForSpawn(x, y)) {
                life_position.setX(x);
                life_position.setY(y);
            }
        }
    }
    QCoreApplication::processEvents();
    repaint();
}

void GameBoard::clearAttack() {
    if(!gameOver() && (alive_squirtles > 0 || alive_charmanders > 0))
        for (int x = 0; x < board_size; x++)
            for (int y = 0; y < board_size; y++)
                if (positionAvailableForSpawn(x, y)) {
                    labels[y * board_size + x]->clear();
                }
}

GameBoard::~GameBoard() {
    delete pika;
    delete [] squirtle_positions;
    delete [] charmander_positions;
}
