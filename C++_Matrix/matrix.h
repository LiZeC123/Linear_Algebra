#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <cstdio>
#include <fstream>

#include "Fraction.h"
#include "Math_Function.h"
#include "Matrix_Exception.h"

class Matrix
{
	friend Matrix operator+(Matrix & lmx, Matrix & rmx);
	friend Matrix operator-(Matrix & lmx, Matrix & rmx);
	friend Matrix operator*(int C, Matrix & rmx);
	friend Matrix operator*(Matrix & lmx, Matrix & rmx);



public:
	Matrix() = default;

public:
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

	//转置矩阵
	Matrix & Transpose();

	//清空矩阵的内容
	Matrix & Clear();

private:
	std::vector<int> buf;
	std::vector<std::vector<int> > content;

	//交换两行
	Matrix & RowEx(int row1, int row2);
	//指定行乘以常数倍
	Matrix & RowExC(int C, int row);
	//指定两行线性组合加到另一行
	Matrix & RowExCP(int C1, int row, int C2, int crow);

	//返回指定行的pivot的索引，即该行第一个非0元素索引，返回行宽度，表示查找失败
	int GetPivot(int row);

	//在未处理的行中，返回指定列的第一个非0元素行数
	//如果本行非0，返回负数，如果全为0，返回行宽度
	int CheckPivot(unsigned int doRow,unsigned int col);

	//去除给定行的公因子
	void Reduceone(int row);

	//返回矩阵中的一列
	std::vector<int> GetCol(int col);


	//将给定的矩阵化成阶梯型
	int _RowReduce_Tri(bool IsDeterminant = false);

	//将给定的有唯一解的阶梯型矩阵化简
	void _RegressReduce();

	//返回阶梯型矩阵的秩
	int _Rank();
};

#endif