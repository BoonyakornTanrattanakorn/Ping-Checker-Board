#ifndef BOARD_H
#define BOARD_H

#define CHECK_BEFORE_MOVING false

#include <bits/stdc++.h>
#include "moveCommand.h"
using namespace std;

class Board{
    public:
        vector<bool> empty_row;
        vector<vector<bool>> board;
        int board_width, board_height;

        Board(int width, int initial_row)
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

        bool tileEmpty(int i, int j){
            return !board[i][j];
        }

        bool leftMoveValid(int i, int j){
            // 1) j-2 is valid and empty tile 
            // 2) j-1 is a piece
            return (j-2 >= 0 and !board[i][j-2]) and board[i][j-1];
        }

        bool rightMoveValid(int i, int j){
            // 1) j+2 is valid and empty tile
            // 2) j+1 is a piece
            return (j+2 < board_width and !board[i][j+2]) and board[i][j+1];
        }

        bool downMoveValid(int i, int j){
            // 1) i+1 is a piece
            return i+1 < board_height and board[i+1][j];
        }

        void performLeftMove(int i, int j){
            #if CHECK_BEFORE_MOVING
                if(!leftMoveValid(i, j)) return;
            #endif
                board[i][j-2] = 1;
                board[i][j-1] = 0;
                board[i][j] = 0;
        }

        void performRightMove(int i, int j){
            #if CHECK_BEFORE_MOVING
                if(!rightMoveValid(i, j)) return;
            #endif
                board[i][j+2] = 1;
                board[i][j+1] = 0;
                board[i][j] = 0;
        }

        void performDownMove(int i, int j){
            #if CHECK_BEFORE_MOVING
                if(!downMoveValid(i, j)) return;
            #endif
                board[i][j] = 0;
                board[i+1][j] = 0;
                ensureHeight(i+2);
                board[i+2][j] = 1;
        }

        bool isMoveValid(int i, int j, int dir){
            if(tileEmpty(i, j)) return false;
            if(dir == -1) return leftMoveValid(i, j);
            if(dir == 0) return downMoveValid(i, j);
            return rightMoveValid(i, j);
        }

        void performMove(int i, int j, int dir){
            #if CHECK_BEFORE_MOVING
                if(tileEmpty(i, j)) return;
            #endif
                if(dir == -1) performLeftMove(i, j);
                else if(dir == 0) performDownMove(i, j);
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
            for(int i = 0; i < board_height; ++i){
                for(int j = 0; j < board_width; ++j){
                    for(int8_t dir = -1; dir <= 1; ++dir){
                        if(isMoveValid(i, j, dir)){
                            
                            out.emplace(moveCommand(i, j, dir));
                        }
                    }
                }
            }
            return out;
        }

        void ensureHeight(int i){
            while(i >= board_height){
                board.resize(i+1, empty_row);
                ++board_height;
            }
        }

        int getHeight(){
            return board_height;
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