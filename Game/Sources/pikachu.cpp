#include "..\Headers\pikachu.h"

Pikachu::Pikachu()
{
    //spawn in middle of bottom row of board facing up
    x = 7, y = 14;
    dir = 0;
    //give 3 lives
    lives = 3;
    max_lives = lives;

    //set images
    QString up_filename = "../Images/Up.png";
    QString down_filename = "../Images/Down.png";
    QString left_filename = "../Images/Left.png";
    QString right_filename = "../Images/Right.png";
    up_image = new QPixmap(up_filename);
    down_image = new QPixmap(down_filename);
    left_image = new QPixmap(left_filename);
    right_image = new QPixmap(right_filename);
}

int Pikachu::get_x() {
    return x;
}

int Pikachu::get_y() {
    return y;
}

int Pikachu::get_dir() {
    return dir;
}

void Pikachu::set_x(int nx) {
    x = nx;
}

void Pikachu::set_y(int ny) {
    y = ny;
}

void Pikachu::set_dir(int d) {
    dir = d;
}

unsigned int Pikachu::get_lives() {
    return lives;
}

void Pikachu::lose_life() {
    if (lives > 0)
        --lives;
}

void Pikachu::gain_life() {
    ++lives;
}

QPixmap* Pikachu::get_up_image() {
    return up_image;
}

QPixmap* Pikachu::get_down_image() {
    return down_image;
}

QPixmap* Pikachu::get_left_image() {
    return left_image;
}

QPixmap* Pikachu::get_right_image() {
    return right_image;
}

Pikachu::~Pikachu() {
}
