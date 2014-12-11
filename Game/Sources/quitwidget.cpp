#include "..\Headers\quitwidget.h"

QuitWidget::QuitWidget(QWidget *parent) :
    QWidget(parent)
{
    //Create confirmation message and buttons
    sure = new QLabel("Are you sure?");
    cancel = new QPushButton("Cancel");
    ok = new QPushButton("OK");

    //Add widgets to layouts
    QHBoxLayout* quit_buttons = new QHBoxLayout;
    quit_buttons->addWidget(ok);
    quit_buttons->addWidget(cancel);

    QVBoxLayout* quit_layout = new QVBoxLayout;
    quit_layout->addWidget(sure);
    quit_layout->addLayout(quit_buttons);

    this->setLayout(quit_layout);

    //Prevent resizing of QuitWidget
    //setFixedSize(1000, 800);

    //Set background color of QuitWidget to black
    //setStyleSheet("background-color : black");

    //Set Window Title to "Title"
    setWindowTitle("Title");

    //Clicking "OK" closes QuitWidget
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(close()));

    //Clicking "Cancel" hides QuitWidget
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(hide()));
}

QuitWidget::~QuitWidget() {
}
