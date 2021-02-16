#include "HugeInt.h"
#include <cstring>
#include <cstdlib>
//#include <iostream>
//using namespace std;
istream & operator >> (istream &input, HugeInt &h)
{
	if(h.x==0 && h.s!="0")
		input >> h.s;
	else if(h.x!=0 && h.s=="0")
		input >> h.x;
	else 
		input >> h.x;
	return input;
}

ostream & operator << (ostream &output, const HugeInt &h)
{
	if(h.x==0 && h.s!="0")
		output << h.s;
	else if(h.x!=0 && h.s=="0")
		output << h.x;
	else 
		output << h.x;
	return output;	
}

HugeInt operator + (HugeInt &h1, const HugeInt &h2)
{
	h1.x += h2.x;
	h1.y = atoi(h1.s);
	h2.y = atoi(h2.s);
//	istringstream (h1.s)>>h1.y;
//	istringstream (h2.s)>>h2.y;
	h1.y += h2.y;
	return h1;
}

HugeInt operator - (HugeInt &h1, const HugeInt &h2)
{
	h1.x -= h2.x;
	h1.y = atoi(h1.s);
	h2.y = atoi(h2.s);
//	istringstream (h1.s)>>h1.y;
//	istringstream (h2.s)>>h2.y;
	h1.y -= h2.y;
	return h1;	
}
