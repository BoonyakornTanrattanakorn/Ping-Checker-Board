#include <unordered_map>
#include <thread>
using namespace std;

#include "boardV3.h"

bool isFinished = false;
int iteration = 0;
unordered_map<Board, pair<uint8_t, stack<moveCommand>>, BoardHash> explored;

pair<uint8_t, stack<moveCommand>> DFS(Board& board){
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

            Board nextState(board);
            nextState.performMove(m);

            pair<uint8_t, stack<moveCommand>> result = DFS(nextState);
            if(result.first > best_result.first){
                  best_result = result;
                  best_move = m;
            }
      }
      best_result.second.emplace(best_move);
      explored[board] = best_result;
      return best_result;
}

// heuristic where pieces should always move to the center
// piece on left should move to right, piece on right should move to left (all piece should move to the center)
// with memorization
pair<uint8_t, stack<moveCommand>> DFS2(Board& board){
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
            
            board.performMove(m);
            pair<uint8_t, stack<moveCommand>> result = DFS2(board);
            board.undoMove(m);
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
      Board tmp(board);
      board.performStarterMove();

      pair<uint8_t, stack<moveCommand>> result = DFS2(board);
      tmp.performStarterMove();
      while(!result.second.empty()){
            tmp.print();
            tmp.performMove(result.second.top());
            result.second.pop();
      }
      tmp.print();
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

void sol(uint8_t board_width, uint8_t board_height){
      explored.clear();
      iteration = 0;
      Board board(board_width, board_height);
      printf("width: %d height %d\n\n", board_width, board_height);
      thread progressThread(progressReport);
      auto start = chrono::high_resolution_clock::now();

      solveByDFS(board);
      isFinished = true;

      auto end = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
      cout << "Execution time: " << duration.count()/1000000.0 << " seconds\n\n";
}

// main(){
//       sol(BOARD_WIDTH, STARTING_HEIGHT);
// }

