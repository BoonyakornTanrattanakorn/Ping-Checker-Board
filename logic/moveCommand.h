#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

using namespace std;

struct moveCommand{
    uint8_t i, j, dir;
    moveCommand(uint8_t row = 0, uint8_t col = 0, uint8_t direction = 0) 
        : i(row), j(col), dir(direction) {}
    
    static constexpr uint8_t LEFT = 0;
    static constexpr uint8_t DOWN = 1;
    static constexpr uint8_t RIGHT = 2;
};

#endif