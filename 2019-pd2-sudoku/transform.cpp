#include <iostream>
#include <cstdlib>
#include <fstream>
#include "sudoku.h"
#define MAX_CASE    100
using namespace std;
int main(int argc, char** argv) {
    int sudoku_in[Sudoku::sudokuSize];
    int incase;
    Sudoku su;
    for(int i=0; i<Sudoku::sudokuSize; ++i)
        cin >> sudoku_in[i];     // read in map
    su.setMap(sudoku_in);  // set map

    while(cin >>incase) {
        switch(incase) {
            int x, y;
        case 0:
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
        case 1:
            cin >> x >> y;
            su.changeNum(x,y);
            break;
        case 2:
            cin >> x >> y;
            su.changeRow(x,y);
            break;
        case 3:
            cin >> x >> y;
            su.changeCol(x,y);
            break;
        case 4:
            cin >> x;
            su.rotate(x);
            break;
        case 5:
            cin >> x;
            su.flip(x);
            break;
        }
    }
}
