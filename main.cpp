#include <bits/stdc++.h>
#include <thread>
using namespace std;


#define BOARD_VERSION 2
#if BOARD_VERSION == 1
      #include "board.h"
#elif BOARD_VERSION == 2
      #include "boardV2.h"
#else
      #include "board.h"
#endif

#define DFS_SOLVE_METHOD 2

bool isFinished = false;
int leaf_node = 0;
int iteration = 0;

pair<uint8_t, stack<moveCommand>> DFS(Board board){
      stack<moveCommand> moves = board.getAllMoves();
      ++iteration;
      if(moves.empty()){
            ++leaf_node;
            return {board.board_height, {}};
      }

      pair<uint8_t, stack<moveCommand>> best_result = {0, {}};
      while(!moves.empty()){
            Board nextState = Board(board);
            nextState.performMove(moves.top());
            pair<uint8_t, stack<moveCommand>> result = DFS(nextState);

            if(result.first > best_result.first){
                  best_result = result;
                  best_result.second.emplace(moves.top());
            }
            moves.pop();
      }

      return best_result;
}

// heuristic where pieces should always move to the center
// piece on left should move to right, piece on right should move to left (all piece should move to the center)
pair<uint8_t, stack<moveCommand>> DFS2(Board board){
      stack<moveCommand> moves = board.getAllMoves();
      ++iteration;
      if(moves.empty()){
            ++leaf_node;
            return {board.board_height, {}};
      }
      pair<uint8_t, stack<moveCommand>> best_result = {0, {}};
      moveCommand best_move;
      while(!moves.empty()){
            moveCommand m = moves.top();
            moves.pop();

            // move left but is left or move right but is right
            if((m.dir == 0 and m.j <= board.board_width/2) or (m.dir == 2 and m.j >= board.board_width/2)) continue;
            Board nextState = Board(board);
            nextState.performMove(m);

            pair<int, stack<moveCommand>> result = DFS2(nextState);
            if(result.first > best_result.first){
                  best_result = result;
                  best_move = m;
            }
      }
      best_result.second.emplace(best_move);
      return best_result;
}

void solveByDFS(Board& board){
      cout << "Solving by brute force depth first search\n";
      board.print();
      board.performStarterMove();
      board.print();
      #if DFS_SOLVE_METHOD == 1
            pair<uint8_t, stack<moveCommand>> result = DFS(board);
      #elif DFS_SOLVE_METHOD == 2
            pair<uint8_t, stack<moveCommand>> result = DFS2(board);
      #else
            pair<uint8_t, stack<moveCommand>> result = DFS(board);
      #endif
      while(!result.second.empty()){
            board.performMove(result.second.top());
            board.print();
            result.second.pop();
      }
      cout << "Final height is: " << result.first << '\n';
      cout << "Amount of leaf node: " << leaf_node << '\n';
      cout << "Total iteration: " << iteration << '\n';
}

void progressReport(){
      auto start = chrono::high_resolution_clock::now();
      this_thread::sleep_for(5000ms);
      while(!isFinished){
            cout << "Leaf node explored: " << leaf_node << '\n';
            cout << "Iteration: " << iteration << '\n';

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Average speed: " << iteration/(duration.count()/1000000.0) << " it/s\n";
            cout << "Elapsed Time: " << duration.count()/1000000.0 << " seconds\n\n";
            this_thread::sleep_for(5000ms);
      }
}

#define BOARD_WIDTH 9
#define BOARD_HEIGHT 2

int main(){
      Board board = Board(BOARD_WIDTH, BOARD_HEIGHT);
      thread progressThread(progressReport);
      auto start = chrono::high_resolution_clock::now();

      solveByDFS(board);
      isFinished = true;

      auto end = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
      cout << "Execution time: " << duration.count()/1000000.0 << " seconds" << endl;
}