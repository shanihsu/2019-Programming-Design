#include <iostream>
#include <fstream>
#include <math.h>
#include "lab2class.h"

using namespace std;
int main(int argc, char** argv) {
	int K;
	float Ra, Rb, Sa;
	score actual;
	fstream fin, fout;
	fin.open("file.in", ios::in);
	fout.open("file.out", ios::out);
	if(!fin)
		cout<<"Fail opening fin!"<<endl;
	if(!fout)
		cout<<"Fail opening fout!"<<endl;
	fin>>K>>Ra>>Rb>>Sa;
	fout<<Ra<<" "<<Rb<<" "<<endl;
	actual.set(Ra, Rb, K);
	actual.calculate(Sa, Ra, Rb, K);
	fout<<actual.getRa()<<" "<<actual.getRb()<<" "<<endl;
	while(fin>>Sa){
		actual.set(Ra, Rb, K);
		actual.calculate(Sa, actual.getRa(), actual.getRb(), K);
		fout<<actual.getRa()<<" "<<actual.getRb()<<" "<<endl;	
	}
	fin.close();
	fout.close();
	return 0;
}
