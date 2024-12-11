#include <bits/stdc++.h>
using namespace std;

#include "board.h"
int leaf_node = 0;
int iteration = 0;

// return max_height
pair<int, stack<moveCommand>> DFS(Board board){
      stack<moveCommand> moves = board.getAllMoves();
      ++iteration;
      if(moves.empty()){
            ++leaf_node;
            return {board.getHeight(), {}};
      }

      pair<int, stack<moveCommand>> best_result = {-1, {}};
      while(!moves.empty()){
            Board nextState = Board(board);
            nextState.performMove(moves.top());
            pair<int, stack<moveCommand>> result = DFS(nextState);

            if(result.first > best_result.first){
                  best_result = result;
                  best_result.second.emplace(moves.top());
            }
            moves.pop();
      }

      return best_result;
}


void solveByDFS(Board& board){
      cout << "Solving by brute force depth first search\n";
      board.print();
      board.performStarterMove();
      board.print();
      pair<int, stack<moveCommand>> result = DFS(board);
      while(!result.second.empty()){
            board.performMove(result.second.top());
            board.print();
            result.second.pop();
      }
      cout << "Final height is: " << result.first << '\n';
      cout << "Amount of leaf node: " << leaf_node << '\n';
      cout << "Total iteration: " << iteration << '\n';
}

int main(){
      Board board = Board(6, 2);
      auto start = chrono::high_resolution_clock::now();

      solveByDFS(board);

      auto end = chrono::high_resolution_clock::now();

      // Calculate the duration
      auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

      cout << "Execution time: " << duration.count()/1000000.0 << " seconds" << endl;
}