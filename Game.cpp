#define default_size 10

#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>
#include "Game.h"

using std::for_each;
using std::mt19937;

Square::Square(int x_pos_in, int y_pos_in, int color_in){
    pos_x = x_pos_in;
    pos_y = y_pos_in;
    color = static_cast<Color_Type>(color_in);
}

#define default_size_square 200

void Game::generate_squares(){
    count_steps = 0;
    count_steps += 1;
    numbers = {1,2,3,4,5,6,7,8,9,10};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            mt19937 eng(time(nullptr));
            int color = eng() % 10 + 1;
            while (numbers.count(color) == 0){
                color = eng() % 10 + 1;
            }
            Square square(default_size_square * i, default_size_square * j, color);
            squares.push_back(square);
            numbers.erase(color);
        }
    }
    free_color = *numbers.begin();
}

void Game::to_do_step(int pos_x, int pos_y){
    count_steps += 1;
    int index = 0;
    for (auto& square : squares){
        if ( ( (square.pos_x / 200) != pos_x) || ( (square.pos_y / 200) != pos_y) ) continue;
        int new_free_color = static_cast<int>(square.color);
        square.color = static_cast<Color_Type>(free_color);
        free_color = new_free_color;
    }
}