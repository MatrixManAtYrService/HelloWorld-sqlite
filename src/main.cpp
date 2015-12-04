#include "helloPrinter.h"
#include <iostream>
using namespace std;

int main()
{
	HelloPrinter printer;
    string something = printer.Hello();

	cout << something;

	cout << "Press ENTER to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return 0;
}
