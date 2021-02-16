#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int main(int argc, char** argv) {
	int i, n, total;
	ifstream fin;
	fin.open("file.in", ios::in);
	if(!fin)
		cout<<"Fail opening fin!"<<endl;
	fin>>n;
	vector <int> v(n);
	for(i=0; i<n; ++i){
		fin>>v.at(i);
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	total = v.at(0) + v.at(1) + v.at(2) + v.at(3) + v.at(4);
	cout<<total<<endl;
	fin.close();
	return 0;
}
