#include <bits/stdc++.h>
using namespace std;


class Board{
    vector<vector<bool>> board;
    int board_width, board_height;

    public:
        Board(int width, int initial_row){
            vector<vector<bool>> tmp(initial_row, vector<bool>(width, 1));
            board = tmp;

            board_width = width;
            board_height = initial_row;
        }

        // move if input are valid
        bool move(int i, int j, int dir){
            // i, j needs to be a piece
            if(!board[i][j]) return false;
            if(dir == -1){
                // left
                // 1) j-2 is valid and empty tile
                // 2) j-1 is a piece
                if((j-2 >= 0 and !board[i][j-2]) and
                    board[i][j-1]){
                    board[i][j-2] = 1;
                    board[i][j-1] = 0;
                    board[i][j] = 0;
                    return true;
                }
            }else if(dir == 0){
                // right
            }else{
                // down
            }
        }

        void print(){
            for(auto i : board){
                for(auto j : i){
                    cout << (j ? '*' : '-') << ' ';
                }
                cout << '\n';
            }
        }
};