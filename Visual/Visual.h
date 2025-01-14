//
// Created by Slawomir on 14.01.2025.
//

#ifndef VISUAL_H
#define VISUAL_H
#include <SFML/Graphics.hpp>

class Visual {
public:
    Visual(double d_win_x,double d_win_y,std::string str_name,double d_grid_x,double d_grid_y);
    ~Visual();
    void vSetColors(std::vector<sf::Color>& vec_colors);
    void vSetPoints(std::vector<std::pair<double,double>> vec_points);
    void vPaint(std::vector<int> vec_int,int i_group_off_set);
    void run();
private:
    const sf::Color color_unknown = sf::Color::Green;
    const sf::Color color_background = sf::Color::Black;
    const sf::Color color_cross = sf::Color::White;


    const double d_win_x;
    const double d_win_y;
    const std::string str_name;

    double d_width=100;
    double d_height=100;
    float d_radius = 5.0f;

    sf::Vector2f vec_center;

    void vClearGrid();
    void vDrawCross();

    sf::RenderWindow* pc_window;
    std::vector<sf::Shape*> vec_grid;
    std::vector<sf::Color> vec_colors;

};



#endif //VISUAL_H
