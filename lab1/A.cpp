#include <iostream>
using namespace std;

void function(int a){
	if(a!=1){
		if(a%2==0)
			a=a/2;
		else
			a=3*a+1;
	cout<<a<<" ";
	function(a);
	}
}

int main(int argc, char** argv) {
	int n;
	cin>>n;
	cout<<n<<" ";
	function(n);
	cout<<endl;
	return 0;
}

