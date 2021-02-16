#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "sudoku.h"
#define MAX_CASE    100
using namespace std;
int main(int argc, char** argv) {
    int sudoku_in[Sudoku::sudokuSize];
    int incase;
    Sudoku su;
    srand(time(NULL)); //Fixed random seed
    int case_rand[20];
    for(int i=0; i<20; ++i) { //Generate random numbers array
        case_rand[i] = rand()%5 + 1;
    }
    ifstream in("sudoku_infile",ios::in);
    for(int i=0; i<Sudoku::sudokuSize; ++i)
        in >> sudoku_in[i];     // read in map
    su.setMap(sudoku_in);  // set map
    for(int i; i<20; ++i) {
        switch(case_rand[i]) {
            int x, y;
        case 1:
            x = rand()%9 + 1; //Generate random numbers
            y = rand()%9 + 1;
            su.changeNum(x,y);
            break;
        case 2:
            x = rand()%3;
            y = rand()%3;
            su.changeRow(x,y);
            break;
        case 3:
            x = rand()%3;
            y = rand()%3;
            su.changeCol(x,y);
            break;
        case 4:
            x = rand()%100 + 1;
            su.rotate(x);
            break;
        case 5:
            x = rand()%2;
            su.flip(x);
            break;
        }
    }
    for(int i=0; i<Sudoku::row; ++i) { //print map
        for(int j=0; j<Sudoku::column; ++j) {
            if(j == 8) {
                cout << su.getElement(i, j);
                cout << endl;
            } else {
                cout << su.getElement(i, j) << " ";
            }
        }
    }
    return 0;
}
