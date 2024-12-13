#ifndef BOARD_V2_H
#define BOARD_V2_H

#include <vector>
#include <bitset>
#include <stack>
#include <iostream>
#include "moveCommand.h"

using namespace std;

class Board {
public:
    vector<bitset<BOARD_WIDTH>> board; // Each bitset represents a row
    uint8_t board_width, board_height;

    // Constructor
    Board(uint8_t width, uint8_t height)
        : board_width(width), board_height(height), board(height, bitset<BOARD_WIDTH>()) {
        for (uint8_t i = 0; i < board_height; ++i) {
            board[i].set(); // Fill all positions with pieces (1)
        }
    }

    // Copy Constructor
    Board(const Board& other)
        : board(other.board),
          board_width(other.board_width),
          board_height(other.board_height) {}

    // Check if a tile is empty
    bool isEmptyTile(uint8_t i, uint8_t j) const {
        return !board[i][j];
    }

    // Check if a tile has a piece
    bool isPiece(uint8_t i, uint8_t j) const {
        return board[i][j];
    }

    // Check if a left move is valid
    bool leftMoveValid(uint8_t i, uint8_t j) const {
        return (j >= 2 && isEmptyTile(i, j - 2) && isPiece(i, j - 1));
    }

    // Check if a right move is valid
    bool rightMoveValid(uint8_t i, uint8_t j) const {
        return (j + 2 < board_width && isEmptyTile(i, j + 2) && isPiece(i, j + 1));
    }

    // Check if a down move is valid
    bool downMoveValid(uint8_t i, uint8_t j) const {
        return (i + 1 < board_height && isPiece(i + 1, j));
    }

    // Check if a move is valid
    bool isMoveValid(uint8_t i, uint8_t j, uint8_t dir) const {
        if (isEmptyTile(i, j)) return false;
        if (dir == 0) return leftMoveValid(i, j);
        if (dir == 1) return downMoveValid(i, j);
        return rightMoveValid(i, j);
    }

    // Perform a left move
    void performLeftMove(uint8_t i, uint8_t j) {
        board[i][j - 2] = 1;
        board[i][j - 1] = 0;
        board[i][j] = 0;
    }

    // Perform a right move
    void performRightMove(uint8_t i, uint8_t j) {
        board[i][j + 2] = 1;
        board[i][j + 1] = 0;
        board[i][j] = 0;
    }

    // Perform a down move
    void performDownMove(uint8_t i, uint8_t j) {
        if (i + 2 >= board_height) {
            board.resize(i + 3, bitset<BOARD_WIDTH>());
            board_height = i + 3;
        }
        board[i + 2][j] = 1;
        board[i + 1][j] = 0;
        board[i][j] = 0;
    }

    // Perform a move based on direction
    void performMove(uint8_t i, uint8_t j, uint8_t dir) {
        if (dir == 0) performLeftMove(i, j);
        else if (dir == 1) performDownMove(i, j);
        else performRightMove(i, j);
    }

    // Perform a move using a moveCommand
    void performMove(moveCommand command) {
        performMove(command.i, command.j, command.dir);
    }

    // Perform the starter move
    void performStarterMove() {
        performDownMove(board_height - 2, board_width / 2);
    }

    // Get all valid moves
    stack<moveCommand> getAllMoves() const {
        stack<moveCommand> out;
        for (uint8_t i = 0; i < board_height; ++i) {
            for (uint8_t j = 0; j < board_width; ++j) {
                for (uint8_t dir = 0; dir < 3; ++dir) {
                    if (isMoveValid(i, j, dir)) out.emplace(i, j, dir);
                }
            }
        }
        return out;
    }

    // Print the board
    void print() const {
        for (uint8_t i = 0; i < board_height; ++i) {
            for (uint8_t j = 0; j < board_width; ++j) {
                cout << (board[i][j] ? '*' : '-') << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }

    // Print a move and its resulting board
    void printMove(moveCommand move) {
        Board tmp(*this);
        tmp.performMove(move);
        tmp.print();
    }

    // Comparison operator for std::map
    bool operator<(const Board& other) const {
        // Compare board dimensions first
        if (board_height != other.board_height) return board_height < other.board_height;
        if (board_width != other.board_width) return board_width < other.board_width;

        // Lexicographical comparison of the vector<bitset>
        for (size_t i = 0; i < board.size(); ++i) {
            if (board[i] != other.board[i]) {
                return board[i].to_ulong() < other.board[i].to_ulong();
            }
        }

        // If all rows are equal, the boards are considered equal
        return false;
    }

    bool operator==(const Board& other) const {
        if (board_height != other.board_height) return false;
        if (board_width != other.board_width) return false;

        for (size_t i = 0; i < board.size(); ++i) {
            if (board[i] != other.board[i]) return false;
        }
        
        return true;
    }
};

struct BoardHash {
    size_t operator()(const Board& board) const {
        size_t hash_value = 0;
        for (const auto& row : board.board) { // Assuming getBitsetRepresentation() returns board rows
            hash_value ^= hash<bitset<BOARD_WIDTH>>{}(row) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
        }
        return hash_value;
    }
};

#endif
