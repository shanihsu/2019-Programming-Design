#include <iostream>
#include "HugeInt.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	HugeInt x;
	HugeInt y(28825252);
	HugeInt z("314159265358979323846");
	HugeInt result;
	cin >> x;
	result = x+y;
	cout << x << "+" << y << " = " << result << endl;
	result = z - x;
	cout << result << endl;
	return 0;
}
