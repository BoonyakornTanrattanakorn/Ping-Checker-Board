#ifndef BOARD_H
#define BOARD_H

#define CHECK_BEFORE_MOVING false

#include <bits/stdc++.h>
#include "moveCommand.h"
using namespace std;

// Easiest implementation with vector
class Board{
    public:
        vector<bool> empty_row;
        vector<vector<bool>> board;
        uint8_t board_width, board_height;

        Board(uint8_t width, uint8_t initial_row)
            : board(initial_row, vector<bool>(width, true)),
              empty_row(width, false),
              board_width(width),
              board_height(initial_row)
        {}

        Board(Board& other)
            : board(other.board),
            empty_row(other.empty_row),
            board_width(other.board_width),
            board_height(other.board_height)
        {
            
        }

        bool tileEmpty(uint8_t i, uint8_t j){
            return !board[i][j];
        }

        bool leftMoveValid(uint8_t i, uint8_t j){
            // 1) j-2 is valid and empty tile 
            // 2) j-1 is a piece
            return (j >= 2 and !board[i][j-2]) and board[i][j-1];
        }

        bool rightMoveValid(uint8_t i, uint8_t j){
            // 1) j+2 is valid and empty tile
            // 2) j+1 is a piece
            return (j+2 < board_width and !board[i][j+2]) and board[i][j+1];
        }

        bool downMoveValid(uint8_t i, uint8_t j){
            // 1) i+1 is a piece
            return i+1 < board_height and board[i+1][j];
        }

        bool isMoveValid(uint8_t i, uint8_t j, uint8_t dir){
            if(tileEmpty(i, j)) return false;
            if(dir == 0) return leftMoveValid(i, j);
            if(dir == 1) return downMoveValid(i, j);
            return rightMoveValid(i, j);
        }

        void performLeftMove(uint8_t i, uint8_t j){
            #if CHECK_BEFORE_MOVING
                if(!leftMoveValid(i, j)) return;
            #endif
                board[i][j-2] = 1;
                board[i][j-1] = 0;
                board[i][j] = 0;
        }

        void performRightMove(uint8_t i, uint8_t j){
            #if CHECK_BEFORE_MOVING
                if(!rightMoveValid(i, j)) return;
            #endif
                board[i][j+2] = 1;
                board[i][j+1] = 0;
                board[i][j] = 0;
        }

        void performDownMove(uint8_t i, uint8_t j){
            #if CHECK_BEFORE_MOVING
                if(!downMoveValid(i, j)) return;
            #endif
                board[i][j] = 0;
                board[i+1][j] = 0;
                ensureHeight(i+2);
                board[i+2][j] = 1;
        }

        void performMove(uint8_t i, uint8_t j, uint8_t dir){
            #if CHECK_BEFORE_MOVING
                if(tileEmpty(i, j)) return;
            #endif
                if(dir == 0) performLeftMove(i, j);
                else if(dir == 1) performDownMove(i, j);
                else performRightMove(i, j);
        }

        void performMove(moveCommand command){
            performMove(command.i, command.j, command.dir);
        }

        void performStarterMove(){
            performDownMove(board_height-2, board_width/2);
        }

        stack<moveCommand> getAllMoves(){
            stack<moveCommand> out;
            for(uint8_t i = 0; i < board_height; ++i){
                for(uint8_t j = 0; j < board_width; ++j){
                    for(uint8_t dir = 0 ; dir < 3; ++dir){
                        if(isMoveValid(i, j, dir)){
                            out.emplace(moveCommand(i, j, dir));
                        }
                    }
                }
            }
            return out;
        }

        void ensureHeight(uint8_t i){
            while(i >= board_height){
                board.resize(i+1, empty_row);
                ++board_height;
            }
        }

        void print(){
            for(auto i : board){
                for(auto j : i){
                    cout << (j ? '*' : '-') << ' ';
                }
                cout << '\n';
            }
            cout << '\n';
        }

        void printMove(moveCommand move){
            Board tmp = Board(*this);
            tmp.performMove(move.i, move.j, move.dir);
            tmp.print();
        }
};

#endif