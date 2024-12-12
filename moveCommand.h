#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <bits/stdc++.h>
using namespace std;

class moveCommand{
    public:
        uint8_t i, j, dir;

        moveCommand(){

        }

        moveCommand(uint8_t row, uint8_t col, uint8_t direction){
            i = row;
            j = col;
            dir = direction;
        }
};

#endif