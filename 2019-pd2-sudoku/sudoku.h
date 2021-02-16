#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

#include <iostream>
#include <ctime>
using namespace std;
class Sudoku {
  public:
    Sudoku();
    Sudoku(const int init_map[]);
    void setMap(const int  set_map[]);
    void changeNum(int x, int y);
    void changeRow(int x,int y);
    void changeCol(int x,int y);
    void rotate(int x);
    void flip(int x);
    int getElement(int index_i, int index_j);
    bool isCorrect();
    static const int sudokuSize = 81;
    static const int row = 9;
    static const int column = 9;
  private:
    bool checkUnity(int arr[]);
    int map[row][column];
};

class Clock {
  public:
    Clock();
    Clock(clock_t s);
    void start();
    void setStart(clock_t start_ts);
    clock_t getStart();
    double getElapsedTime();
  private:
    clock_t start_ts;
};
#endif //SUDOKU_H
/*class Sudoku
{
public:
    Sudoku();

    // generate
    static Sudoku generate();

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int solve();
};
*/
