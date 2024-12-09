#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
///FOR API
#include <curl/curl.h>
#include <nlohmann/json.hpp>
///FOR TIME
#include <chrono>
#include <ctime>

using namespace std::chrono;
using namespace std::literals::chrono_literals;

using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string getTemperature(const std::string& apiKey) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.openweathermap.org/data/2.5/weather?q=Moscow,ru&appid=" + apiKey + "&units=metric";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            json j = json::parse(readBuffer);
            return std::to_string(j["main"]["temp"].get<double>());
        }
    }
    return "Error";
}


void drawwing(Game& game, vector<sf::Color> colors, sf::RenderWindow& window);

int main()
{
    
  
    Game game;
    game.generate_squares();
 
    sf::RenderWindow window(sf::VideoMode(800,700), "SFML works!");
        

    
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
                    drawwing(game, colors, window);
                }
            }
            
        }
        window.display();
    }
    return 0;
}

std::string check_color_text(Square square, int& color_index){
    color_index = 1;
    switch(static_cast<int>(square.color))
    {
        case 1:
            return "White";
        case 2:
            color_index = 0;
            return "Black";
        case 3:
            return "Brown";
        case 4:
            return "Blue";
        case 5:
            return "Light_Blue";
        case 6:
            return "Red";             
        case 7: 
            return "Yellow";
        case 8:
            return "Green";
        case 9:
            return "Gray";
        case 10:
            return "Pink";          
    }
    return "Undefined";
}

void drawwing(Game& game, vector<sf::Color> colors, sf::RenderWindow& window){
     sf::Font font;
    font.loadFromFile("Hayamichi.ttf");
    sf::Text text;
    text.setFont(font);
    window.clear();
    for (auto& square : game.squares){
        sf::RectangleShape Rect(sf::Vector2f(200.f, 200.f));
        Rect.setFillColor(colors[static_cast<int>(square.color)-1]);
        Rect.setPosition(square.pos_x, square.pos_y);
        int color_text = 0;
        text.setString(check_color_text(square, color_text));
        text.setPosition(square.pos_x+10, square.pos_y+10);
        text.setFillColor(colors[color_text]);
        window.draw(Rect);     
        window.draw(text);
    }

    //For board
    sf::RectangleShape Rect_x_board(sf::Vector2f(600.f, 1.f));
    Rect_x_board.setFillColor(colors[0]);
    sf::RectangleShape Rect_y_board(sf::Vector2f(1.f, 600.f));
    Rect_y_board.setFillColor(colors[0]);
    Rect_x_board.setPosition(0.f, 600.f);
    Rect_y_board.setPosition(600.f, 0.f);
    window.draw(Rect_x_board);
    window.draw(Rect_y_board);

    //For count steps
   
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setString("Count steps is: " + std::to_string(game.count_steps)); 
    text.setPosition(200.f, 610.f); 
    window.draw(text);

    //For temperature
    using json = nlohmann::json;

    std::string apiKey = "65a8a5b1c7a28f1459473df987bd2008"; 
    std::string temperature_in_Moscow = "Temperature \nin Moscow:\n" + getTemperature(apiKey) + " °C";

    text.setString(temperature_in_Moscow);
    text.setPosition(610.f, 100.f);
    window.draw(text);

    //For time
    time_point now = system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&tt); 
    std::string cur_data = std::to_string(tm->tm_year + 1900) + "-" + std::to_string(tm->tm_mon + 1) + "-" + std::to_string(tm->tm_mday);
    std::string cur_time = std::to_string(tm->tm_hour) + ":" + std::to_string(tm->tm_min);
    std::string time = cur_data + '\n' + cur_time;
     text.setString(time);
    text.setPosition(610.f, 400.f);
    window.draw(text);

    window.display();

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
