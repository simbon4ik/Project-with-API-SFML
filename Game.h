#ifndef GAME
#define GAME

#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;
class Square;

class Game{
        public:
        vector<Square> squares;
        void generate_squares();
        unordered_set<int> numbers;
        int free_color;
        void to_do_step(int pos_x, int pos_y);
        int count_steps;
};

enum class Color_Type {White = 1, Black, Brown, Blue, Light_Blue, Red, Yellow, Green, Gray, Pink};

class Square{
        public:
        int pos_x;
        int pos_y;
        Color_Type color;
        Square();
        Square(int pos_x_in, int pos_y_in, int color_in);
};

class Player{
        public:
        ///
};


#endif
