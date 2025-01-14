//
// Created by Slawomir on 14.01.2025.
//

#include "Visual.h"


Visual::Visual(double d_win_x, double d_win_y, std::string str_name, double d_grid_x, double d_grid_y) : d_win_x(d_win_x),d_win_y(d_win_y),str_name(str_name) {
    pc_window = nullptr;
    d_width = d_grid_x>0 ? d_grid_x : d_width;
    d_height = d_grid_y>0 ? d_grid_y : d_height;
}

Visual::~Visual() {
    delete pc_window;
    vClearGrid();
}

void Visual::vSetColors(std::vector<sf::Color> &vec_colors) {
    this->vec_colors = vec_colors;
}

void Visual::vSetPoints(std::vector<std::pair<double, double>> vec_points) {
    vClearGrid();
    vec_grid.resize(vec_points.size());
    for (int i=0; i<vec_points.size(); i++) {
        double d_pos_x = vec_points[i].first * (d_win_x / d_width) + d_win_x/2;
        double d_pos_y = vec_points[i].second * (d_win_y / d_height) + d_win_y/2;
        vec_grid[i] = new sf::CircleShape(d_radius);
        vec_grid[i]->setPosition(d_pos_x, d_pos_y);
        vec_grid[i]->setFillColor(color_unknown);
    }
}

void Visual::vPaint(std::vector<int> vec_int,int i_group_off_set) {
    for (int i = 0; i<vec_grid.size() && i<vec_int.size(); i++) {
        if (vec_int[i]-i_group_off_set<vec_colors.size()) {
            vec_grid[i]->setFillColor(vec_colors[vec_int[i]]);
        }
    }
}



void Visual::run() {
    pc_window = new sf::RenderWindow(sf::VideoMode(d_win_x, d_win_y), str_name, sf::Style::Titlebar | sf::Style::Close);
    pc_window->setFramerateLimit(60);
    pc_window->setVisible(true);
    while (pc_window->isOpen()) // Pętla działa, dopóki użytkownik nie zamknie okna
    {
        sf::Event event;
        while (pc_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                pc_window->close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    pc_window->close();
                }
            }
        }
        if (vec_grid.size()==0)printf("empty grid\n");
        pc_window->clear(color_background);
        vDrawCross();
        for (auto& e : vec_grid) pc_window->draw(*e);
        pc_window->display();
    }
}



void Visual::vClearGrid() {
    for (auto& e : vec_grid) {
        delete e;
    }
    vec_grid.clear();
}

void Visual::vDrawCross() {
    sf::Vector2u windowSize = pc_window->getSize();
    sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);

    // Tworzenie prostokąta do rysowania poziomej linii
    sf::RectangleShape horizontalLine(sf::Vector2f(windowSize.x, 2.f));
    horizontalLine.setFillColor(color_cross);
    horizontalLine.setPosition(0.f, center.y - 1.f);  // Ustawienie pozycji na środku pionowo

    // Tworzenie prostokąta do rysowania pionowej linii
    sf::RectangleShape verticalLine(sf::Vector2f(2.f, windowSize.y));
    verticalLine.setFillColor(color_cross);
    verticalLine.setPosition(center.x - 1.f, 0.f);  // Ustawienie pozycji na środku poziomo

    // Rysowanie krzyża
    pc_window->draw(horizontalLine);
   pc_window->draw(verticalLine);
}