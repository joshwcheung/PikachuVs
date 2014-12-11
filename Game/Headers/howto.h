#ifndef HOWTO_H
#define HOWTO_H

#include "mainwindow.h"
#include "quitwidget.h"
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QLabel>
#include <QRect>
#include <QWidget>

/**
 * @brief The HowTo class displays controls for how the game is played\n
 * @QPushButton* back closes HowTo, taking the user back to the MainWindow
 */

class HowTo : public QWidget
{
    Q_OBJECT

public:
    explicit HowTo(QWidget *parent = 0);
    ~HowTo();

private:

    //QPushButton
    QPushButton* back;

};

#endif // HOWTO_H
