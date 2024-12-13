#ifndef BOARD_V2_H
#define BOARD_V2_H

#define CHECK_BEFORE_MOVING false

#include <bits/stdc++.h>
#include "moveCommand.h"
using namespace std;

// Optimized implementation with unordered_set
class Board{
    public:
        set<pair<uint8_t, uint8_t>> board;
        uint8_t board_width, board_height;

        Board(uint8_t width, uint8_t height)
            : board_width(width),
              board_height(height)
        {
            for(uint8_t i = 0; i < board_height; ++i){
                for(uint8_t j = 0; j < board_width; ++j){
                    board.insert({i, j});
                }
            }
        }

        Board(const Board& other)
            : board(other.board),
              board_width(other.board_width),
              board_height(other.board_height)
        {
        }

        bool isEmptyTile(uint8_t i, uint8_t j){
            return board.find({i, j}) == board.end();
        }

        bool isPiece(uint8_t i, uint8_t j){
            return board.find({i, j}) != board.end();
        }

        bool leftMoveValid(uint8_t i, uint8_t j){
            // 1) j-2 is valid and empty tile 
            // 2) j-1 is a piece
            return (j >= 2 and isEmptyTile(i, j-2)) and (isPiece(i, j-1));
        }

        bool rightMoveValid(uint8_t i, uint8_t j){
            // 1) j+2 is valid and empty tile
            // 2) j+1 is a piece
            return (j+2 < board_width and isEmptyTile(i, j+2)) and (isPiece(i, j+1));
        }

        bool downMoveValid(uint8_t i, uint8_t j){
            // 1) i+1 is a piece
            return isPiece(i+1, j);
        }

        bool isMoveValid(uint8_t i, uint8_t j, uint8_t dir){
            if(isEmptyTile(i, j)) return false;
            if(dir == 0) return leftMoveValid(i, j);
            if(dir == 1) return downMoveValid(i, j);
            return rightMoveValid(i, j);
        }

        void performLeftMove(uint8_t i, uint8_t j){
            #if CHECK_BEFORE_MOVING
                if(!leftMoveValid(i, j)) return;
            #endif
                board.insert({i, j-2});
                board.erase({i, j-1});
                board.erase({i, j});
        }

        void performRightMove(uint8_t i, uint8_t j){
            #if CHECK_BEFORE_MOVING
                if(!rightMoveValid(i, j)) return;
            #endif
                board.insert({i, j+2});
                board.erase({i, j+1});
                board.erase({i, j});
        }

        void performDownMove(uint8_t i, uint8_t j){
            #if CHECK_BEFORE_MOVING
                if(!downMoveValid(i, j)) return;
            #endif
                board.erase({i, j});
                board.erase({i+1, j});
                board.insert({i+2, j});
                if(i+2 >= board_height){
                    board_height = i+3;
                }
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
            for(pair<uint8_t, uint8_t> p : board){
                for(uint8_t dir = 0 ; dir < 3; ++dir){
                    if(isMoveValid(p.first, p.second, dir)) out.emplace(moveCommand(p.first, p.second, dir));
                }
            }
            return out;
        }

        void print() {
            vector<vector<char>> display(board_height, vector<char>(board_width, '-'));
            for (const auto& p : board) {
                display[p.first][p.second] = '*';
            }
            for (const auto& row : display) {
                for (char cell : row) cout << cell << ' ';
                cout << '\n';
            }
            cout << '\n';
        }

        void printMove(moveCommand move){
            Board tmp = Board(*this);
            tmp.performMove(move.i, move.j, move.dir);
            tmp.print();
        }

        
        bool operator<(const Board& other) const {
            return board < other.board;
        }

};

#endif