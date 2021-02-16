#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() {
    for(int i=0; i<row; ++i) {
        for(int j=0; j<column; ++j) {
            map[i][j] = 0;
        }
    }
}
Sudoku::Sudoku(const int init_map[]) {
    for(int i=0; i<row; ++i) {
        for(int j=0; j<column; ++j) {
            map[i][j] = init_map[i*9+j];
        }
    }
}

void Sudoku::setMap(const int set_map[]) {
    for(int i=0; i<row; ++i) {
        for(int j=0; j<column; ++j) {
            map[i][j] = set_map[i*9+j];
        }
    }
}
void Sudoku::changeNum(int x, int y) {
    for(int i=0; i<row; ++i) {
        for(int j=0; j<column; ++j) {
            if(map[i][j] == x)
                map[i][j] = -1;
            else if(map[i][j] == y)
                map[i][j] = -2;
        }
    }
    for(int i=0; i<row; ++i) {
        for(int j=0; j<column; ++j) {
            if(map[i][j] == -1)
                map[i][j] = y;
            else if(map[i][j] == -2)
                map[i][j] = x;
        }
    }
}
void Sudoku::changeRow(int x, int y) {
    int tmp[row][column];
    for(int i=3*x; i<3*x+3; ++i) {
        for(int j=0; j<column; ++j) {
            tmp[i][j] = map[i][j];
            map[i][j] = map[i+(y-x)*3][j];
            map[i+(y-x)*3][j] = tmp[i][j];
        }
    }
}
void Sudoku::changeCol(int x, int y) {
    int tmp[row][column];
    for(int j=3*x; j<3*x+3; ++j) {
        for(int i=0; i<row; ++i) {
            tmp[i][j] = map[i][j];
            map[i][j] = map[i][j+(y-x)*3];
            map[i][j+(y-x)*3] = tmp[i][j];
        }
    }
}
void Sudoku::rotate(int x) {
    int actual = x % 4;
    int tmp[row][column];
    for(int k=0; k<actual; k++) {
        for(int i=0; i<row; ++i) {
            for(int j=0; j<column; ++j) {
                tmp[i][j] = map[i][j];
            }
        }
        for(int i=0; i<row; ++i) {
            for(int j=0; j<column; ++j) {
                map[i][j] = tmp[8-j][i];
            }
        }
    }
}
void Sudoku::flip(int x) {
    int tmp[row][column];
    if(x == 0) {
        for(int i=0; i<4; ++i) {
            for(int j=0; j<column; ++j) {
                tmp[i][j] = map[i][j];
                map[i][j] = map[8-i][j];
                map[8-i][j] = tmp[i][j];
            }
        }
    } else {
        for(int j=0; j<4; ++j) {
            for(int i=0; i<row; ++i) {
                tmp[i][j] = map[i][j];
                map[i][j] = map[i][8-j];
                map[i][8-j] = tmp[i][j];
            }
        }
    }
}
int Sudoku::getElement(int index_i, int index_j) {
    return map[index_i][index_j];
}



Clock::Clock() {
    setStart(0);
}
Clock::Clock(clock_t s) {
    setStart(s);
}
void Clock::start() {
    setStart(clock());
}
void Clock::setStart(clock_t ts) {
    start_ts = (ts>0)?ts:clock();
}
clock_t Clock::getStart() {
    return start_ts;
}
double Clock::getElapsedTime() {
    return static_cast<double>(clock()-getStart())/ CLOCKS_PER_SEC ;
}
/*bool Sudoku::checkUnity(int arr[])
{
	int arr_unity[9];   // counters
	for(int i=0; i<9; ++i)
		arr_unity[i] = 0;    // initialize
	for(int i=0; i<9; ++i)
		++arr_unity[arr[i]-1];    // count
	for(int i=0; i<9; ++i)
		if(arr_unity[i] != 1)   // all element
			return false;          // must be 1
	return true;
}
bool Sudoku::isCorrect()
{
	bool check_result;
	int check_arr[9];
	int location;
	for(int i=0; i<81; i+=9)    // check rows
	{
		for(int j=0; j<9; ++j)
			check_arr[j] = map[i+j];
		check_result = checkUnity(check_arr);
		if(check_result == false)
			return false;

	}
	for(int i=0; i<9; ++i)   // check columns
	{
		for(int j=0; j<9; ++j)
			check_arr[j] = map[i+9*j];
		check_result = checkUnity(check_arr);
		if(check_result == false)
			return false;
	}
	for(int i=0; i<9; ++i)   // check cells
	{
		for(int j=0; j<9; ++j)
		{
			location = 27*(i/3) + 3*(i%3)  +9*(j/3) + (j%3);
			check_arr[j] = map[location];
		}
		check_result = checkUnity(check_arr);
		if(check_result == false)
			return false;
	}
	return true;
}*/
