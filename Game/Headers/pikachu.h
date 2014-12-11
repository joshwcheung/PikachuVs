#ifndef PIKACHU_H
#define PIKACHU_H

#include <QLabel>

/**
 * @brief The Pikachu class is the user controlled Pikachu\n
 * @int x, y store the coordinates\n
 * @unsigned int lives stores the number of lives\n
 * @unsigned int max_lives stores the max number of lives\n
 * @unsigned int dir represents direction (0 = up, 1 = down, 2 = left, 3 = right)\n
 * @QPixmap* up_image stores the facing up image\n
 * @QPixmap* down_image stores the facing down image\n
 * @QPixmap* left_image stores the facing left image\n
 * @QPixmap* right_image stores the facing right image
 */

class Pikachu
{

public:

    Pikachu();

    /**
     * @brief get_x returns x
     * @return x
     */

    int get_x();

    /**
     * @brief get_y returns y
     * @return y
     */

    int get_y();

    /**
     * @brief get_dir returns dir
     * @return dir
     */

    int get_dir();

    /**
     * @brief set_x sets x
     * @param nx the input x coordinate
     */

    void set_x(int nx);

    /**
     * @brief set_y sets y
     * @param ny the input y coordinate
     */

    void set_y(int ny);

    /**
     * @brief set_dir sets dir
     * @param d the input dir
     */

    void set_dir(int d);

    /**
     * @brief get_lives returns lives
     * @return lives
     */

    unsigned int get_lives();

    /**
     * @brief lose_life decrements lives
     */

    void lose_life();

    /**
     * @brief gain_life increments lives
     */

    void gain_life();

    /**
     * @brief get_up_image returns up_image
     * @return up_image
     */

    QPixmap* get_up_image();

    /**
     * @brief get_down_image returns down_image
     * @return down_image
     */

    QPixmap* get_down_image();

    /**
     * @brief get_left_image returns left_image
     * @return left_image
     */

    QPixmap* get_left_image();

    /**
     * @brief get_right_image returns right_image
     * @return right_image
     */

    QPixmap* get_right_image();

    ~Pikachu();

private:

    //properties
    int x, y;
    unsigned int lives;
    unsigned int max_lives;
    unsigned int dir;

    //images
    QPixmap* up_image;
    QPixmap* down_image;
    QPixmap* left_image;
    QPixmap* right_image;
};

#endif // PIKACHU_H
