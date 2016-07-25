#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <cstdio>
#include <fstream>

#include "Fraction.h"
#include "Math_Function.h"

class Matrix
{
	friend Matrix operator+(Matrix & lmx, Matrix & rmx);
	friend Matrix operator-(Matrix & lmx, Matrix & rmx);
	friend Matrix operator*(int C, Matrix & rmx);
	friend Matrix operator*(Matrix & lmx, Matrix & rmx);



public:
	//construcor
	Matrix() = default;

	//function
	//向缓冲区读入一个数据
	Matrix & GetOne(int one);
	//将缓冲区的数据写入
	Matrix & ReFlash();
	//将当前矩阵中的内容输出到cout
	void ShowMatrix();
	//判断是否是一个规则的矩阵
	bool IsRegular();
	//判断矩阵是否为空
	bool IsEmpty();
	//判断缓冲区是否为空
	bool IsBufEmpty();
	//对矩阵化简，可以用于求解线性方程组	
	Matrix & RowReduce();	
	//计算对应行列式的值
	Fraction det();

	//清空矩阵的内容
	Matrix & Clear();





private:
	std::vector<int> buf;
	std::vector<std::vector<int> > content;

	//三个初等行变换
	//交换两行
	Matrix & RowEx(int row1, int row2);
	//指定行乘以常数倍
	Matrix & RowExC(int C, int row);
	//指定两行线性组合加到另一行
	Matrix & RowExCP(int C1, int row, int C2, int crow);

	//返回指定行的pivot，即该行第一个非0元素的值
	//若全为0，则返回0
	int GetPivot(int row);

	//检查pivot是否为0
	//如果是，返回第一个不是0的行，如果不存在，返回0
	//如果不是，返回一个负数
	int CheckPivot(int row);

	//返回增广矩阵中对应行的b的值
	int Getb(int row);

	//去除给定行的公因子
	void Reduceone(int row);
	
	//将给定的矩阵化成阶梯型
	int _RowReduce_Tri(bool IsDeterminant = false);
	//将给定的有唯一解的阶梯型矩阵化简
	void _RowReduce_Only();

	//返回阶梯型矩阵的秩
	int _Rank();

	//返回矩阵中的一列
	std::vector<int> GetCol(int col);

};


#endif