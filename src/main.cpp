#include "helloPrinter.h"
#include <iostream>
#include <limits>
using namespace std;

int main()
{
	HelloPrinter printer;
    string something = printer.Hello();

	cout << something;

	cout << "Press ENTER to continue...";                   // this is necessary for when the program is run in a window
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return 0;
}
