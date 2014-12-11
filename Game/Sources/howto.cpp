#include "..\Headers\howto.h"

HowTo::HowTo(QWidget *parent) :
    QWidget(parent)
{
    //Create labels detailing controls
    QLabel* controls = new QLabel("Controls");
    QLabel* up = new QLabel("Move Up:");
    QLabel* down = new QLabel("Move Down:");
    QLabel* left = new QLabel("Move Left:");
    QLabel* right = new QLabel("Move Right:");
    QLabel* upattack = new QLabel("Attack Up:");
    QLabel* downattack = new QLabel("Attack Down:");
    QLabel* leftattack = new QLabel("Attack Left:");
    QLabel* rightattack = new QLabel("Attack Right:");

    QLabel* wkey = new QLabel;
    QLabel* skey = new QLabel;
    QLabel* akey = new QLabel;
    QLabel* dkey = new QLabel;
    QLabel* upkey = new QLabel;
    QLabel* downkey = new QLabel;
    QLabel* leftkey = new QLabel;
    QLabel* rightkey = new QLabel;

    wkey->setPixmap(QPixmap("../Images/Key_W.png"));
    skey->setPixmap(QPixmap("../Images/Key_S.png"));
    akey->setPixmap(QPixmap("../Images/Key_A.png"));
    dkey->setPixmap(QPixmap("../Images/Key_D.png"));
    upkey->setPixmap(QPixmap("../Images/Key_Up.png"));
    downkey->setPixmap(QPixmap("../Images/Key_Down.png"));
    leftkey->setPixmap(QPixmap("../Images/Key_Left.png"));
    rightkey->setPixmap(QPixmap("../Images/Key_Right.png"));
    wkey->setFixedSize(100, 100);
    skey->setFixedSize(100, 100);
    akey->setFixedSize(100, 100);
    dkey->setFixedSize(100, 100);
    upkey->setFixedSize(100, 100);
    downkey->setFixedSize(100, 100);
    leftkey->setFixedSize(100, 100);
    rightkey->setFixedSize(100, 100);

    //Format labels
    QFont font = controls->font();
    font.setPointSize(50);
    font.setBold(true);
    controls->setFont(font);
    font.setPointSize(30);
    font.setBold(false);
    up->setFont(font);
    down->setFont(font);
    left->setFont(font);
    right->setFont(font);
    upattack->setFont(font);
    downattack->setFont(font);
    leftattack->setFont(font);
    rightattack->setFont(font);

    //Left column a
    QVBoxLayout* control_info1 = new QVBoxLayout;
    control_info1->addWidget(up);
    control_info1->addWidget(down);
    control_info1->addWidget(left);
    control_info1->addWidget(right);

    //Left column b
    QVBoxLayout* control_info2 = new QVBoxLayout;
    control_info2->addWidget(wkey);
    control_info2->addWidget(skey);
    control_info2->addWidget(akey);
    control_info2->addWidget(dkey);

    //Right column a
    QVBoxLayout* control_info3 = new QVBoxLayout;
    control_info3->addWidget(upattack);
    control_info3->addWidget(downattack);
    control_info3->addWidget(leftattack);
    control_info3->addWidget(rightattack);

    //Right column b
    QVBoxLayout* control_info4 = new QVBoxLayout;
    control_info4->addWidget(upkey);
    control_info4->addWidget(downkey);
    control_info4->addWidget(leftkey);
    control_info4->addWidget(rightkey);

    //Left columns together
    QHBoxLayout* left_control = new QHBoxLayout;
    left_control->addLayout(control_info1);
    left_control->addLayout(control_info2);

    //Right columns together
    QHBoxLayout* right_control = new QHBoxLayout;
    right_control->addLayout(control_info3);
    right_control->addLayout(control_info4);

    //All columns together
    QHBoxLayout* all_control = new QHBoxLayout;
    all_control->addLayout(left_control);
    QSpacerItem* horizontal_space = new QSpacerItem(250, 10);
    all_control->addSpacerItem(horizontal_space);
    all_control->addLayout(right_control);

    //Create button
    back = new QPushButton("Back");
    font.setPointSize(50);
    back->setFont(font);

    //Combine layouts
    QVBoxLayout* all = new QVBoxLayout;
    all->addWidget(controls, 0, Qt::AlignCenter);
    all->addLayout(all_control);
    all->addWidget(back);

    //Back button closes the HowTo screen
    QObject::connect(back, SIGNAL(clicked()), this, SLOT(hide()));

    this->setLayout(all);

    //Adjust size of window according to desktop
    QDesktopWidget desktop;
    QRect screen = desktop.availableGeometry();
    setFixedSize(screen.width() - 14, screen.height() - 36);

    //Set background color of MainWindow to black
    //setStyleSheet("background-color : black");

    //Set Window Title to "Title"
    setWindowTitle("Title");
}

HowTo::~HowTo() {
}
