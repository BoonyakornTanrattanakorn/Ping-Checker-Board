#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <bits/stdc++.h>
#include "board.h"
using namespace std;

class moveCommand{
    public:
        int i, j;
        int8_t dir;

        moveCommand(){

        }

        moveCommand(int row, int col, int8_t direction){
            i = row;
            j = col;
            dir = direction;
        }
};

#endif