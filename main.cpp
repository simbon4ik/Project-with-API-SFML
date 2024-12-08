#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

void drawwing(Game& game, vector<sf::Color> colors, sf::RenderWindow& window);

int main()
{
    Game game;
    game.generate_squares();
 
    sf::RenderWindow window(sf::VideoMode(600,700), "SFML works!");
        

    
    sf::Color White = sf::Color::White;
    sf::Color Black = sf::Color::Black;
    sf::Color Brown(139, 69, 19);      // Коричневый
    sf::Color Blue(0, 0, 255);         // Синий
    sf::Color LightBlue(173, 216, 230); // Голубой
    sf::Color Red(255, 0, 0);          // Красный
    sf::Color Yellow(255, 255, 0);     // Желтый
    sf::Color Green(0, 255, 0);        // Зеленый
    sf::Color Gray(128, 128, 128);    // Серый
    sf::Color Pink(255, 192, 203);    // Розовый

    vector<sf::Color> colors = {White, Black, Brown, Blue, LightBlue, Red, Yellow, Green, Gray, Pink};

    drawwing(game, colors, window);

     

    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int pos_x = event.mouseButton.x / 200;
                    int pos_y = event.mouseButton.y / 200;
                    game.to_do_step(pos_x, pos_y);
                    std::cout << "Free color is : " << game.free_color << std::endl;
                    drawwing(game, colors, window);
                }
            }
            
        }
        window.display();
    }
    return 0;
}


void drawwing(Game& game, vector<sf::Color> colors, sf::RenderWindow& window){
    window.clear();
    for (auto& square : game.squares){
        sf::RectangleShape Rect(sf::Vector2f(200.f, 200.f));
        Rect.setFillColor(colors[static_cast<int>(square.color)-1]);
        Rect.setPosition(square.pos_x, square.pos_y);
        window.draw(Rect);
    }
    window.display();
    sf::Font font;
    font.loadFromFile("Hayamichi.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setString("Count steps is: " + std::to_string(game.count_steps)); 
    text.setPosition(200.f, 610.f); 
    window.draw(text);
}
/*


            Cell cell = cells[current_pos[0] + x][current_pos[1] + y];
            if (cell.ptr_entities.size() == 0){
                 continue;
            }else for(shared_ptr<Entity> entity : cell.ptr_entities){
                if (dynamic_pointer_cast<Enemy>(entity) != nullptr){
                    attack_enemy(dynamic_pointer_cast<Enemy>(entity));
                }
                */
