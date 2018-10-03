#include <iostream>
#include "sudokusolver.h"
using namespace std;

/*
 We're creating a puzzle here and putting in values.
 It'll first print out the puzzle, then, if it's
 solvable, it'll print out the solution and if not
 it will say the puzzle isn't solvable.
*/

int main()
{
    SudokuPuzzle puzzle;
    
    puzzle.setValue(0, 1, 6);
    puzzle.setValue(1, 1, 8);
    puzzle.setValue(1, 2, 9);
    
    puzzle.setValue(4, 0, 6);
    puzzle.setValue(4, 1, 7);
    puzzle.setValue(5, 2, 4);
    
    puzzle.setValue(6, 0, 7);
    puzzle.setValue(7, 1, 9);
    
    puzzle.setValue(0, 3, 8);
    puzzle.setValue(1, 3, 2);
    puzzle.setValue(1, 5, 5);
    
    puzzle.setValue(3, 4, 6);
    puzzle.setValue(5, 5, 3);
    
    puzzle.setValue(6, 4, 9);
    puzzle.setValue(8, 5, 8);
    
    puzzle.setValue(1, 7, 4);
    puzzle.setValue(2, 8, 3);
    
    puzzle.setValue(4, 7, 5);
    puzzle.setValue(5, 8, 8);
    
    puzzle.setValue(8, 6, 4);
    puzzle.setValue(7, 7, 3);
    puzzle.setValue(8, 7, 6);
    
    puzzle.print();
    cout << endl;
    
    if (puzzle.solve())
    {
        cout << "Here is the solution:" << endl;
        puzzle.print();
    }
    
    else
    {
        cout << "Puzzle is not solvable.";
    }
    
    cout << endl;
    
    return 0;
}
