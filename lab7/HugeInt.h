#include <string>
#include <sstream>   
using namespace std;

class HugeInt{
	friend istream & operator >> (istream &, HugeInt &);
	friend ostream & operator << (ostream &, const HugeInt &);
	friend HugeInt operator + (HugeInt &, const HugeInt &);
	friend HugeInt operator - (HugeInt &, const HugeInt &);
	public:
		HugeInt(){x = 0;s = "0";};
		HugeInt(long long int a){x = a;s = "0";};
		HugeInt(string b){x = 0;s = b;};
		long long int x;
		int y;
		string s;
};
