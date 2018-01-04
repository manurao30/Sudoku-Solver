//
//  sudokusolver.cpp
//  sudoku solver
//
//  Created by Manish Rao on 1/2/18.
//  Copyright © 2018 Manish Rao. All rights reserved.
//

#include "sudokusolver.h"
#include <iostream>
using namespace std;

//Constructor- initializes the puzzle spaces to zero.
//This shows that a value for that spot hasn't been found yet
SudokuPuzzle::SudokuPuzzle(){
    debug = false;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            board[i][j] = 0;
        }
    }
}

/*
 Print out an unsolved puzzle first, in this case take this example
 -------------------------------
 | .  .  . | .  6  . | 7  .  . |
 | 6  8  . | .  7  . | .  9  . |
 | .  9  . | .  .  4 | .  .  . |
 -------------------------------
 | 8  2  . | .  .  . | .  .  . |
 | .  .  . | 6  .  . | 9  .  . |
 | .  5  . | .  .  3 | .  .  8 |
 -------------------------------
 | .  .  . | .  .  . | .  .  4 |
 | .  4  . | .  5  . | .  3  6 |
 | .  .  3 | .  .  8 | .  .  . |
 -------------------------------
Here's the solved version
 -------------------------------
 | 1  3  4 | 5  6  9 | 7  8  2 |
 | 6  8  5 | 2  7  1 | 4  9  3 |
 | 2  9  7 | 8  3  4 | 5  6  1 |
 -------------------------------
 | 8  2  6 | 9  4  5 | 3  1  7 |
 | 3  7  1 | 6  8  2 | 9  4  5 |
 | 4  5  9 | 7  1  3 | 6  2  8 |
 -------------------------------
 | 5  1  2 | 3  9  6 | 8  7  4 |
 | 9  4  8 | 1  5  7 | 2  3  6 |
 | 7  6  3 | 4  2  8 | 1  5  9 |
 -------------------------------
 */

void SudokuPuzzle::print(){
    for(int j = 0; j < 9; j++)
    {
        if(j % 3 == 0)
        {
            cout << "-------------------------------" << endl;
        }
        
        for(int i = 0; i < 9; i++)
        {
            if(i % 3 == 0)
            {
                cout << "|";
            }
            
            if(board[i][j] != 0)
            {
                cout << " " << board[i][j] << " ";
            }
            else
            {
                cout << " . ";
            }
        }
        cout << "|" << endl;
    }
    cout << "-------------------------------" << endl;
}

/*
 Set a value on the board. Used in two instances
 ==> when the initial board is laid
 ==> when a value is found that we're testing during the solve function
 Parameters are:
 cx - x-coordinate, must be between 0 and 8
 cy - y-coordinate, must be between 0 and 8
 value - value to try or the value used when initializing the board
*/

void SudokuPuzzle::setValue(int cx, int cy, int value)
{
    board[cx][cy] = value;
}

bool SudokuPuzzle::solve()
{
    return solve(0,0);
}

int SudokuPuzzle::getValue(int cx, int cy)
{
    return board[cx][cy];
}

/*
 The recursive part of the solution. The parametes are 
 cx - x-coordinate, must be between 0 and 8
 cy - y-coordinate, must be between 0 and 8
 The function would return true if solved and false if it can't be solved
*/

bool SudokuPuzzle::solve(int cx, int cy)
{
    //the stopping condition - only solve the puzzle if it hasn't been solved yet
    if(board[cx][cy] != 0)
    {
        //if the value worked go to the next one
        if(check(cx, cy))
        {
            //at the last block of the puzzle, which means it is solved
            if(cx == 8 && cy == 8)
            {
                return true;
            }
            
            //find the next block on the same row
            int xnext = cx + 1;
            int ynext = cy;
            
            //we're at the end of the row, start at the next one
            if(xnext >= 9)
            {
                xnext = 0;
                ynext++;
            }
            //move to the next piece
            return solve(xnext, ynext);
        }
        //doesn't work
        else
        {
            return false;
        }
    }
    //guess the values until it works
    for(int val = 1; val < 10; val++)
    {
        setValue(cx, cy, val);
        
        //if the value worked, move on to the next one
        if(check(cx, cy))
        {
            //it's the last piece, which means it's solved
            if(cx == 8 && cy == 8)
            {
                return true;
            }
            
            //find next block on the row
            int xnext = cx + 1;
            int ynext = cy;
            
            //we're at the end of the row, start at the new row
            if(xnext >= 9)
            {
                xnext = 0;
                ynext++;
            }
            
            //move to the next piece, return solve
            if(solve(xnext, ynext))
            {
                return true;
            }
        }
    }
    //remove the value, initialize to zero so that the algorithm
    //wouldn't think it's solved
    board[cx][cy] = 0;
    //we haven't found the value, so we have to backtrack
    return false;
}

/*
 This is the main rule-checker function.
 It makes sure that all the values set at 
 locations follow the rules of Sudoku
 The parameters are:
 cx - x-coordinate, must be between 0 and 8
 cy - y-coordinate, must be between 0 and 8
 The function would return true if valid
 and false otherwise
*/

bool SudokuPuzzle::check(int cx, int cy)
{
    printTrace(cx, cy);
    int value = board[cx][cy];
    
    //this makes sure there is no vertical collision
    for(int xcheck = 0; xcheck < 9; xcheck++)
    {
        //make sure we skip the block that we're on right now
        if(xcheck == cx)
        {
            continue;
        }
        
        //if it's the same value, then the number can't be placed
        //in that block ==> failed
        int checkValue = board[xcheck][cy];
        
        if(checkValue == value)
        {
            return false;
        }
    }
    
    //this makes sure there is no horizontal collision
    for(int ycheck = 0; ycheck < 9; ycheck++)
    {
        //make sure we skip the block that we're on right now
        if(ycheck == cy)
        {
            continue;
        }
        
        //if it's the same value, then the number can't be placed
        //in that block ==> failed
        int checkValue = board[cx][ycheck];
        
        if(checkValue == value)
        {
            return false;
        }
    }
    
    //now that we're done with the line, we have to focus on
    //the box, so make sure there is no collision in the box
    int xbox = cx/3;    //here, we get only 3 boxes as the x-coordinate
    int ybox = cy/3;    //here, we get only 3 boxes as the y-coordinate
    
    //for every y
    for(int ycheck = ybox * 3; ycheck < ybox * 3 + 3; ycheck++)
    {
        //for every x
        for(int xcheck = xbox * 3; xcheck < xbox * 3 + 3; xcheck++)
        {
            //make sure we skip the block that we're on right now
            if(xcheck == cx && ycheck == cy)
            {
                continue;
            }
            
            //if it's the same value, then the number can't be placed
            //in that block ==> failed
            int checkValue = board[xcheck][ycheck];
            
            if (checkValue == value)
            {
                return false;
            }
        }
    }
    //we checked that value, so it must be true
    return true;
}

/*
 This function prints out tracers if debug is set to true 
 in the constructor. This is done while recursively solving 
 the puzzle. The parameters are:
 cx - x-coordinate, must be between 0 and 8
 cy - y-coordinate, must be between 0 and 8
*/
void SudokuPuzzle::printTrace(int cx, int cy)
{
    if(debug)
    {
        for (int i = 0; i < cx + cy; i++)
        {
            cout << "";
        }
        cout << "Trying value " << board[cx][cy] << " at board[" << cx << "][" << cy << "]" << endl;
    }
}
