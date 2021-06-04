// C++ program to demonstrate insertion 
// into a vector of vectors 
  
#include <iostream> 
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <string>
#include <stack>
//#include<bits/stdc++.h>
using namespace std; 

// This class keeps pairs of string. This is useful for simulating the recursion through as stack.
class Pair
{
    public:
        int row;
        int col;
};

bool safe_to_place(int** board, int row, int col, int n);

// CODE FOR CREATING BOARD FROM:
// https://www.techiedelight.com/dynamic-memory-allocation-in-c-for-2d-3d-array/
// used the 2nd method (Array of Pointers) as guidance
int** create_board(int n) {

  // allocate memory for n rows
  int** board = new int*[n];

  // allocate memory for n columns
  for (int i = 0; i < n; i++) {
    board[i] = new int[n];
  }

  // initialize board to all 0s
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }

  return board;

}

// Function to print the entire board (used for debugging)
void print_board(int** board, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

// Function to deallocate memory for the entire board
void free_board(int** board, int n) {
  for (int i = 0; i < n; i++) {
    delete[] board[i];
  }
  delete[] board;
  return;
}


// Function to check whether input queens are valid and place them if they are
// returns true if all input queens were able to be placed on the board
// returns false if function was unable to place queens (either because of collisions or because
// the indexes were out of bounds --> greater than board size or less than zero)
bool place_queens(int** board, int n, int num_queens, vector<int>rows, vector<int>cols) {
  
  // loop to iterate through the input queen positions
  for (int i = 0; i < num_queens; i++) {
    if ((rows[i] < n) && (rows[i] >= 0)) {    // checks if row entry is a valid position
      if ((cols[i] < n) && (cols[i] >= 0)) {  // checks if col entry is a valid position
        if (safe_to_place(board, rows[i], cols[i], n)) {  // checks if queen is safe to place
          board[rows[i]][cols[i]] = 1;        // places queen
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    } 
  }
  return true; // if queen was able to be placed successfully, return true
}

// function used for stack solving algorithm during backtracking
// used to check if there is already a queen in the current column
bool queen_in_col(int** board, int row, int col, int n) {

  // checks if there is a queen ABOVE current position
  for (int i = row; i >= 0; i--) {
    if (board[i][col]) {
      return true;
    }
  }

  // checks if there is a queen BELOW current position
  for (int i = row; i < n; i++) {
    if (board[i][col]) {
      return true;
    }
  }

  return false; // returns false if no queen was found
}

// Function to check if a queen is safe to place in a given position
// checks both left and right upper diagonals, as well as lower left and right diagonals
// checks left and right side of row and above and below the position in the column
bool safe_to_place(int** board, int row, int col, int n) {

  // check if there is a queen in the row to left
  for (int i = 0; i < col; i++) {
    if (board[row][i]) {
      return false;
    }
  }

  // check if there is a queen in the row to right
  for (int i = col; i < n; i++) {
    if (board[row][i]) {
      return false;
    }
  }

  // check if there is a queen in the column above
  for (int i = row; i >= 0; i--) {
    if (board[i][col]) {
      return false;
    }
  }

  // check if there is a queen in the column below
  for (int i = row; i < n; i++) {
    if (board[i][col]) {
      return false;
    }
  }

  // check if there is a queen on the upper left diagonal
  for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j]) {
      return false;
    }
  }

  // check if there is a queen on the lower left diagonal
  for (int i = row, j = col; i < n && j >= 0; i++, j--) {
    if (board[i][j]) {
      return false;
    }
  }

  // check if there is a queen on the upper right diagonal
  for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
    if (board[i][j]) {
      return false;
    }
  }

  // check if there is a queen on the lower right diagonal
  for (int i = row, j = col; i < n && j < n; i++, j++) {
    if (board[i][j]) {
      return false;
    }
  }
  return true;  // returns true if the queen is safe to place
                // returns false if otherwise
}

// Function to find a value in a given vector v
// used to check if there is an input queen in a given column
bool find_vec(vector<int> v, int x) {
  if (std::find(v.begin(), v.end(), x) != v.end()) {
    return true;
  } else {
    return false;
  }
} 

// Function used to solve the N-Queens problem using a Stack
bool Solve_Stack(int** board, int n, vector<int>v) {

  stack <class Pair> queens_stack; // stack to hold all positions of placed queens
  stack <class Pair> next_check;   // stack to hold the next position to check
  Pair init, stack_top;
  init.row = 0;               
  init.col = 0;
  next_check.push(init);            // first spot to check is the position (0,0) on n x n chessboard
                                    // for the purpose of solving the problem, chessboard is indexed starting 0

  while(!next_check.empty()) {      // continue until there are no spots left to check
    
    stack_top = next_check.top();   // pop the next check
    next_check.pop();
    
    
    if (stack_top.col >= n) {       // return true if we are checking in the last column
      return true;
    }

    if (find_vec(v, stack_top.col)) {  // if there is an input queen in this col
      Pair to_push;
      to_push.row = stack_top.row;
      to_push.col = stack_top.col + 1;
      next_check.push(to_push);        // skip to check next column
      continue;
    }

    for (int i = 0; i < n; i++) {   // iterate through each row in the given column
      if (safe_to_place(board, i, stack_top.col, n)) {  // if position in row i, col = stacktop is safe
        board[i][stack_top.col] = 1;     // place queen

        Pair to_push;
        to_push.row = i;
        to_push.col = stack_top.col;
        queens_stack.push(to_push);      // push position to queens stack
        to_push.row = stack_top.row;
        to_push.col = stack_top.col + 1;
        next_check.push(to_push);        // set next check equal to row 0 on the next column
        break;                           // break out of loop
      }

      if (queen_in_col(board, i, stack_top.col, n)) {  // if there is already a queen in this column
        Pair to_delete = queens_stack.top();           // delete the last queen placed
        queens_stack.pop();
        board[to_delete.row][to_delete.col] = 0;       // reset the board
        i = to_delete.row;                             // set i = row that was deleted
        stack_top.col = to_delete.col;                 // set col to check = col that was deleted
        continue;
      }

      if (i == n-1) {                               // if i = n-1 (at the last row)
        if (queens_stack.empty()) {                 // and there are no queens left to backtrack / delete
          return false;                             // then return false
        }
        Pair to_delete = queens_stack.top();        // delete the last placed queen (backtrack)
        queens_stack.pop();
        board[to_delete.row][to_delete.col] = 0;    // reset board position

        if ((i == n-1) && (queens_stack.empty())) { // if queen stack is empty after popping
          i = to_delete.row;                        // set i = recently deleted row
          stack_top.col = to_delete.col;            // set col = recently deleted col
          continue;                                 // continue through the loop
        }

        i = to_delete.row;
        stack_top.col = to_delete.col;

        if (queens_stack.empty()) {                 // if queen stack is still empty, return false
          return false;
        }
        
        if (i == n-1) {                             // if we have still hit the last row
          Pair next;
          next = queens_stack.top();
          next_check.push(next);                    // next check is the position of last pushed queen
        }
        
        continue;
      }
    }
  }
  return false; // once exited out of while loop, return false if no solution was found
}




 
// Dynamic Memory Allocation in C++ for 2D Array
int main(int argc, char** argv) {

  if (argc < 3) {
    throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); //throw error
  }

  ifstream input;   // stream for input file
  ofstream output;  // stream for output file

  input.open(argv[1]);  // open input file
  output.open(argv[2]); // open output file

  int n = 0; // store input size;

  string in_str;        // string to store line read from input file
  char* tok_str;        // pointer to store null terminated version of in_str
  char* token;          // pointer to store strtok string

  vector<int> in_row;   // vector to hold all input queens' row positions
  vector<int> in_col;   // vector to hold all input queens' col positions

  while (getline(input, in_str)) {      // while loop to parse through input file strings
    tok_str = strdup(in_str.c_str());   // add null terminator and duplicate input string

    token = strtok(tok_str, " ");       // tokenize input string
    n = stoi(token);                    // store board size
    token = strtok(NULL, " ");

    if (n <= 3) {                       // if board size is less than or equal to 3   
      output << "No solution" << endl;  // print no solution to output file and continue to read next line
      continue;
    }

    int** board = create_board(n);      // if board size is valid, create board

    vector<int> inputs;                 // function to store all inputs

    int in_count = 0;                   // int to count number of input positions (x2 because it counts pairs individually)
    while(token != NULL) {              // while loop to read through string and push integers to vector
      inputs.push_back(stoi(token));
      token = strtok(NULL, " ");
      in_count += 1;                    // increment counter after reading each row/col position
    }

    if (in_count % 2 != 0) {            // check if there are matching pairs for row/col positions
      output << "No solution" << endl;  // if not: print no solution to output file and continue
      continue;
    } 

    // put inputs into rows and cols vectors
    int x = 0;
    int while_count = in_count;
    while(while_count > 0) {
      if (x % 2 == 0) {                 // if input is a column, push to column vector
        in_col.push_back(inputs[x] - 1);
      } else {                          // if input is a row, push to row vector
        in_row.push_back(inputs[x] - 1);
      }
      while_count -= 1;
      x += 1;
    }

    int len = in_count / 2;             // number of row/col ints in the vector
    if (place_queens(board, n, len, in_row, in_col)) {  // check if input queen positions are valid and place them if yes

      if(!Solve_Stack(board, n, in_col)) {          // solve the problem using stack algorithm
        output << "No solution" << endl;            // if function returns false: print no solution
      } else {                                      // else:
        for (int i = 0; i < n; i++) {               // iterate through board and print the position of each queen
          for (int j = 0; j < n; j++) {             // to the output file
            if (board[j][i]) {
              output << i+1 << " " << j+1 << " ";
            }
          }
        }
        output << endl;
      }
    } else {
      output << "No solution" << endl; // if input queens were not able to be placed, print no solution
    }


    for (int i = 0; i < len; i++) {    // reset the input row and input column vector to read in next set
      in_col.erase(in_col.begin()+0);  // of positions from the next line
      in_row.erase(in_row.begin()+0);
    }

    free_board(board, n);              // free memory allocated to current board (since new board is created
                                       // during each iteration of reading the strings regardless
  }

  return 0;

}
