#include <iostream>
#define UNASSIGNED 0
#define N 9
#define M 10
using namespace std;
int blank;
int count = 0;

/*void print(int ques[9][9], int plist[81][3]) {
    cout << endl;
    for(int i=0; i<blank; ++i) {
        cout << plist[i][2] << " ";
    }
    cout << endl;
    for(int i=0; i<9; ++i) {
        for(int j=0; j<9; ++j) {
            cout << ques[i][j] << " ";
        }
        cout << endl;
    }
}
*/
bool isUsed(int RowData[N][M], int ColData[N][M], int BoxData[N][M], int i, int j, int value) {
    if(RowData[i][value] == 1 || ColData[j][value] == 1 || BoxData[(i/3)*3+j/3][value] == 1) {
        return true;
    }
    return false;
}

int getMin(int plist[81][3]) {
    int index, min = 10;
    for(int i=0; i<blank; ++i) {
        if(plist[i][2]<min) {
            min = plist[i][2];
            index = i;
        }
    }
    return index;
}

bool SolveSudoku(int ques[N][N],int RowData[N][M], int ColData[N][M], int BoxData[N][M], int plist[81][3], int l, int p) {
    count++;
    if(l == 0)
        return true;
    int row, col, surerow, surecol, surebox;

    row = plist[p][0];
    col = plist[p][1];

    for (int num = 1; num <= N; ++num) {
        if(RowData[row][num] == 1 || ColData[col][num] == 1 || BoxData[(row/3)*3+col/3][num] == 1)
            continue;

        ques[row][col] = num;
        int tempArr[blank];
        for(int t=0; t<blank; ++t) {
            tempArr[t] = plist[t][2];
        }
        int tempNum = plist[p][2];
        int temp = p;
        for(int t=0; t<blank; ++t) {
            if((row == plist[t][0] || col == plist[t][1] || (row/3)*3+col/3 == (plist[t][0]/3)*3+plist[t][1]/3) && !isUsed(RowData, ColData, BoxData, plist[t][0], plist[t][1], num)) {
                plist[t][2]--;
            }
        }
        RowData[row][num] = 1;
        ColData[col][num] = 1;
        BoxData[(row/3)*3+col/3][num] = 1;
        plist[p][2] = 10;
        l--;
        p = getMin(plist);
        //cout << row << ", " << col << endl << endl;
        //print(ques, plist);
        if (SolveSudoku(ques, RowData, ColData, BoxData, plist, l, p))
            return true;

        ques[row][col] = UNASSIGNED;
        RowData[row][num] = UNASSIGNED;
        ColData[col][num] = UNASSIGNED;
        BoxData[(row/3)*3+col/3][num] = UNASSIGNED;
        p = temp;
        plist[p][2] = tempNum;
        for(int t=0; t<blank; ++t) {
            plist[t][2] = tempArr[t];
        }
        l++;
    }
    return false; // this triggers backtracking
}

/*		int tempNum = plist[p][2];
		int temp = p;
		plist[p][2] = 10;
		l--;
		p = getMin(plist);
*/

/*		p = temp;
		plist[p][2] = tempNum;
		l++;
*/

int main() {
    int ques[N][N];
    int plist[81][3]; //Find row and col where blank is
    int l = 0;
    int p = 0;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin>>ques[i][j];
            if(ques[i][j] == UNASSIGNED) {
                plist[l][0] = i;
                plist[l][1] = j;
                plist[l][2] = 9;
                l++;
            }
        }
    }
    blank = l;
    int RowData[N][M];
    int ColData[N][M];
    int BoxData[N][M];
    for(int i = 0; i<N; ++i) {
        for(int j = 0; j<M; ++j) {
            RowData[i][j] = UNASSIGNED;
            ColData[i][j] = UNASSIGNED;
            BoxData[i][j] = UNASSIGNED;
        }
    }
    for(int i = 0; i<N; ++i) {
        for(int j = 0; j<N; ++j) {
            RowData[i][ques[i][j]] = 1;
            ColData[j][ques[i][j]] = 1;
            BoxData[(i/3)*3+j/3][ques[i][j]] = 1;
        }
    }

    for(int i=0; i<l; ++i) {
        for(int j=1; j<M; ++j) {
            if(isUsed(RowData, ColData, BoxData, plist[i][0], plist[i][1], j))
                plist[i][2]--;
        }
    }

    p = getMin(plist);
    /*	for(int i=0; i<blank; ++i){
    		cout << plist[i][2] << " ";
    	}
    */	if(l > 64)
        cout << 2 <<endl;
    else if (SolveSudoku(ques, RowData, ColData, BoxData, plist, l, p) == true) {
        cout << 1 << endl;
        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                if(col == 8) {
                    cout<<ques[row][col];
                    cout << endl;
                } else {
                    cout<<ques[row][col] << " ";
                }
            }
        }
    } else
        cout<<0<<endl;
    return 0;
}
