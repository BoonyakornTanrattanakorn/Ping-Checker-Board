#include <bits/stdc++.h>
#include <thread>
#include "config.h"
using namespace std;


#if BOARD_VERSION == 1
      #include "board.h"
#elif BOARD_VERSION == 2
      #include "boardV2.h"
#elif BOARD_VERSION == 3
      #include "boardV3.h"
#endif


bool isFinished = false;
int iteration = 0;
int max_height = 0;
unordered_map<Board, pair<uint8_t, stack<moveCommand>>, BoardHash> explored;

pair<uint8_t, stack<moveCommand>> DFS(Board board){
      stack<moveCommand> moves = board.getAllMoves();
      ++iteration;
      if(moves.empty()){
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
// with memorization
pair<uint8_t, stack<moveCommand>> DFS2(Board board){
      ++iteration;
      auto it = explored.find(board);
      if(it != explored.end()){
            return (*it).second;
      }
      stack<moveCommand> moves = board.getAllMoves();
      if(moves.empty()){
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

            pair<uint8_t, stack<moveCommand>> result = DFS2(nextState);
            if(result.first > best_result.first){
                  best_result = result;
                  best_move = m;
            }
      }
      best_result.second.emplace(best_move);
      explored[board] = best_result;
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
      cout << "Final height is: " << (int)result.first << '\n';
      cout << "Total iteration: " << iteration << '\n';
}

void progressReport(){
      auto start = chrono::high_resolution_clock::now();
      this_thread::sleep_for(5000ms);
      while(!isFinished){
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            printf("Iteration: %d\nAverage speed: %.01f it/s\nElapsed Time: %.01f seconds\n\n", iteration, iteration/(duration.count()/1000000.0), duration.count()/1000000.0);
            this_thread::sleep_for(5000ms);
      }
}

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