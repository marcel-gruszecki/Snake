#ifndef MAIN_HPP
#define MAIN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

#define WIDTH_X 74
#define HIGHT_Y 56
#define WIDTH 815
#define HIGHT 617
#define FPS 7

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Snake {
public:
    std::vector<std::pair<int, int>> position;  
    direction dir;                         
    std::pair<int,int> snack;               

    Snake();
    ~Snake();

    void print(sf::RenderWindow& window);   
    void move(direction n);                 
    void change_direction(direction n);     
    void is_collision();                   
    void reset_position();                  
    void eating();                          
    void snack_generator();                
};

int bounded_rand(int range); 

#endif 
