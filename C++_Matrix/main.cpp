#include "matrix.h"
#include <iostream>

#define TEST_NUM 25

using std::cin; using std::cout; using std::endl;

int main()
{
	Matrix Rc;
	int temp;
	int column, count = 1;
	std::cout << "please input the column of the matrix:";
	std::cin >> column;
	for (int i = 0; i < TEST_NUM; ++i) 
	{
		std::cin >> temp;
		Rc.GetOne(temp);
		if (count != column) {
			++count;
		}
		else
		{
			Rc.ReFlash();
			count = 1;
		}
	}

	if (Rc.IsRegular())
	{
		Rc.ShowMatrix();
	}
	else
	{
		std::cout << "input is not a matrix" << std::endl;
	}
	
	int cmd;
	int row1, row2, c;
	while (std::cin >> cmd)
	{

		if (cmd == 1) {
			Rc.RowReduce();
		}
		else if (cmd == 2) {
			Fraction Fc;
			Fc = Rc.det();
			Fc.ShowFraction();
		}
		Rc.ShowMatrix();
	}

}