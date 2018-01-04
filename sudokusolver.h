//
//  sudokusolver.h
//  sudoku solver
//
//  Created by Manish Rao on 1/2/18.
//  Copyright © 2018 Manish Rao. All rights reserved.
//

#ifndef sudokusolver_h
#define sudokusolver_h

class SudokuPuzzle
{
    private:
        short int board[9][9];              //represents the board - 0 if a value isn't set, 1-9 if valid
        bool debug;                         //used to set trace on
        void printTrace(int cx, int cy);    //prints the current tracing value
        bool solve(int cx, int cy);         //recursive method - tries to solve the block one at a time
        bool check(int cx, int cy);         //verifies if the set value is correct
    
    public:
        SudokuPuzzle();                     //constructor
        void print();                       //prints the current state of the puzzle
        void setValue(int cx, int cy, int value);      //sets the value of the board, used for layout and to solve
        int getValue(int cx, int cy);      //gets a value on the board
        bool solve();                       //solves the puzzle, returns true if it can be solved, false if not
};

#endif /* sudokusolver_h */
