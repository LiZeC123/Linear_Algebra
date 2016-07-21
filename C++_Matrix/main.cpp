#include "matrix.h"
#include <iostream>

using std::cin; using std::cout; using std::endl;

Matrix Rc;

void Input();

int main()
{

	cout << "Welcome to Use EasyMatLab" << endl;
	cout << ">>>";

	
	char cmd;
	int row1, row2, c;
	while (cin >> cmd) {
		if (cmd == 'i') {
			Input();
		}
		else if (cmd = 'r') {
			Rc.RowReduce();
			Rc.ShowMatrix();
		}
		cout << ">>>";
	}
}


void Input() {
	int temp;
	int column, count = 1;
	std::cout << "Input>";
	char  cmd;

	while (std::cin >> cmd) {
		if (cmd == 'a') {
			while (std::cin >> temp) {
				Rc.GetOne(temp);
			}
			cout << "Success to add data" << endl;
		}
		if (cmd == 'f') {
			Rc.ReFlash();
			cout << "Buf is clean now" << endl;
		}
		else {
			cout << cmd << "is not define" << endl;
		}
	}

	if (Rc.IsRegular())
	{
		cout << "There is the Matrix that you input:" << endl;
		Rc.ShowMatrix();
	}
	else
	{
		std::cout << "Input is not a matrix" << std::endl;
		Rc.ShowMatrix();
	}
}