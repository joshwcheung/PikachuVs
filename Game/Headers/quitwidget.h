#ifndef QUITWIDGET_H
#define QUITWIDGET_H

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

/**
 * @brief The QuitWidget class displays the confirmation message upon exit\n
 * @QPushButton* ok closes the application when clicked\n
 * @QLabel* sure displays the confirmation message\n
 * @QPushButton* cancel returns the user to the main menu
 */

class QuitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuitWidget(QWidget *parent = 0);
    ~QuitWidget();

    //Buttons (called in main)
    QPushButton* ok;

private:

    //Confirmation message
    QLabel* sure;

    //Buttons
    QPushButton* cancel;

};

#endif // QUITWIDGET_H
