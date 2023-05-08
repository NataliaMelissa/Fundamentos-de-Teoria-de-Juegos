#include "Error.h"
#include <iostream>

void FatalError(string ErrorString) {
	cout << ErrorString << endl;
	cout << "Enter any key to quit " << endl;

	int tmp;
	cin >> tmp;

	exit(-1);
}