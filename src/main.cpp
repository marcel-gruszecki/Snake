#include "main.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

Snake::Snake() {
    position = {{35, 28}, {36, 28}, {37, 28}};
    dir = LEFT;
    snack_generator();
}

Snake::~Snake() {
}

void Snake::move(direction n) {
    std::pair<int, int> new_head = position.front();
    switch (n) {
        case UP: {
            new_head.second -= 1;
            break;
        }

        case DOWN: {
            new_head.second += 1;
            break;
        }

        case LEFT: {
            new_head.first -= 1;
            break;
        }

        case RIGHT: {
            new_head.first += 1;
            break;
        }

        default: {
            break;
        }
    }

    for(int i = position.size() - 1; i > 0; i--) {
        position[i] = position[i - 1];
    }

    position[0] = new_head;
}

void Snake::change_direction(direction n) {
    if(dir == UP && n != DOWN) {
        dir = n;
    }else if(dir == DOWN && n != UP) {
        dir = n;
    }else if(dir == LEFT && n != RIGHT) {
        dir = n;
    }else if(dir == RIGHT && n != LEFT) {
        dir = n;
    }
}

void Snake::reset_position() {
    position = {{35, 28}, {36, 28}, {37, 28}};
    snack_generator();
    dir = LEFT;
}

void Snake::is_collision() {
    int x = position.front().first;
    int y = position.front().second;
    if(x < 0 || y < 0) {
        reset_position();
    }else if(x == WIDTH_X || y == HIGHT_Y) {
        reset_position();
    }

    for(long unsigned int i = 1; i < position.size(); i++) {
        if(x == position[i].first && y == position[i].second) {
            reset_position();
            break;
        }
    }
}

void Snake::eating() {
    
    std::pair<int, int> head = position.front();
    std::pair<int, int> last_element = position.back();
    std::pair<int, int> pre_last_element = position[position.size() - 2];
    std::pair<int, int> change_of_position = {last_element.first - pre_last_element.first, last_element.second - pre_last_element.second};
    if(head.first == snack.first && head.second == snack.second) {
        std::cout << "eating" << std::endl;
        change_of_position.first += last_element.first;
        change_of_position.second += last_element.second;
        position.push_back(change_of_position);
        snack_generator();
    }

    
}

int bounded_rand(int range) {
    return rand() % range;
}

void Snake::snack_generator() {
    bool is_empty = false;
    int x;
    int y;
    while(!is_empty) {
        x = bounded_rand(74);
        y = bounded_rand(56);

        is_empty = true;

        for(const auto& i : position) {
            if(x == i.first && y == i.second) {
                is_empty = false;
                break;
            }
        }
    }
    //std::cout << x << " " << y << std::endl;
    snack.first = x;
    snack.second = y;

}

void Snake::print(sf::RenderWindow& window) {
    int x, y;
    for(const auto& i : position) {
        //std::cout << i.first << " " << i.second << std::endl;
        x = i.first;
        y = i.second;
        
        sf::RectangleShape rectangle(sf::Vector2f(10.f, 10.f));
        rectangle.setFillColor(sf::Color(0, 0, 204));  
        rectangle.setPosition(x * 11 + 1, y * 11 + 1);
        window.draw(rectangle);
    }

    //Snack
    sf::RectangleShape rectangle(sf::Vector2f(10.f, 10.f));
    rectangle.setFillColor(sf::Color(255, 0, 0));  
    rectangle.setPosition(snack.first * 11 + 1, snack.second * 11 + 1);
    window.draw(rectangle);
}


int main() {
    std::srand(std::time(nullptr));

    sf::RenderWindow window(
        sf::VideoMode({WIDTH + 170, HIGHT}), 
        "Snake",
        sf::Style::Titlebar | sf::Style::Close //Resize is locked
    );

    window.setFramerateLimit(FPS);

    window.setPosition(sf::Vector2i((1920 - WIDTH) / 2, (1080 - HIGHT) / 2));

    sf::Font font;
    if (!font.loadFromFile("fonts/Verdana.ttf")) {
        std::cerr << "Font error!!!" << std::endl;
    }

    // sf::Vector2u size = window.getSize();
    // unsigned int width = size.x;
    // unsigned int height = size.y;

    int best_score = 0;

    Snake snake;

    while (window.isOpen()) {
        window.clear(sf::Color::Black); // lub zielony
        sf::Event event;
        // while there are pending events...
        while (window.pollEvent(event)) {
            // check the type of the event...
            switch (event.type) {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                // key pressed
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Up: //sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                            std::cout << "UP" << std::endl;
                            snake.change_direction(UP);
                            break;
                        case sf::Keyboard::Down:
                            std::cout << "DOWN" << std::endl;
                            snake.change_direction(DOWN);
                            break;
                        case sf::Keyboard::Left:
                            std::cout << "LEFT" << std::endl;
                            snake.change_direction(LEFT);
                            break;
                        case sf::Keyboard::Right:
                            std::cout << "RIGHT" << std::endl;
                            snake.change_direction(RIGHT);
                            break;
                        case sf::Keyboard::Escape:
                            std::cout << "Escape -> Closing" << std::endl;
                            window.close();
                            break;
                        default:
                            std::cout << "Another key: " << event.key.code << std::endl;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

            for(int i = 1; i < WIDTH; i += 11) {
                //x = 0;
                for(int j = 1; j < HIGHT; j += 11) {
                    sf::RectangleShape rectangle(sf::Vector2f(10.f, 10.f));
                    if((i + j) % 2 == 0) {
                        rectangle.setFillColor(sf::Color(15,181,37));
                    }else {
                        rectangle.setFillColor(sf::Color(14,233,43));
                    }
                    
                    rectangle.setPosition(i,j);
                    window.draw(rectangle);
                }
            }



            snake.print(window);

            snake.move(snake.dir);

            snake.is_collision();

            snake.eating();
            
            if(best_score < snake.position.size() - 3) {
                best_score = snake.position.size() - 3;
            }

            //std::cout << "Snake: " << snake.position.front().first << " " << snake.position.front().second << std::endl;

            sf::Text text;
            text.setFont(font); 
            text.setString("Best score " + std::to_string(best_score));
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(820, 0);
            window.draw(text);
            
            text.setFont(font); 
            text.setString("Score " + std::to_string(snake.position.size() - 3));
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(820, 20);
            window.draw(text);
            // std::cout << "Points: " << snake.position.size() - 3 << std::endl;
            //window.clear(sf::Color::Green);
            window.display();


        
    }


    return 0;
}