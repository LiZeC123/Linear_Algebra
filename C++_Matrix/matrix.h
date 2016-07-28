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
	//�򻺳�������һ������
	Matrix & GetOne(int one);

	//��������������д��
	Matrix & ReFlash();

	//����ǰ�����е����������cout
	void ShowMatrix();

	//�ж��Ƿ���һ������ľ���
	bool IsRegular();
	
	//�жϾ����Ƿ�Ϊ��
	bool IsEmpty();

	//�жϻ������Ƿ�Ϊ��
	bool IsBufEmpty();

	//�Ծ��󻯼򣬿�������������Է�����	
	Matrix & RowReduce();	

	//�����Ӧ����ʽ��ֵ
	Fraction det();

	//ת�þ���
	Matrix & Transpose();

	//��վ��������
	Matrix & Clear();

private:
	std::vector<int> buf;
	std::vector<std::vector<int> > content;

	//��������
	Matrix & RowEx(int row1, int row2);
	//ָ���г��Գ�����
	Matrix & RowExC(int C, int row);
	//ָ������������ϼӵ���һ��
	Matrix & RowExCP(int C1, int row, int C2, int crow);

	//����ָ���е�pivot�������������е�һ����0Ԫ�������������п�ȣ���ʾ����ʧ��
	int GetPivot(int row);

	//��δ��������У�����ָ���еĵ�һ����0Ԫ������
	//������з�0�����ظ��������ȫΪ0�������п��
	int CheckPivot(unsigned int doRow,unsigned int col);

	//ȥ�������еĹ�����
	void Reduceone(int row);

	//���ؾ����е�һ��
	std::vector<int> GetCol(int col);


	//�������ľ��󻯳ɽ�����
	int _RowReduce_Tri(bool IsDeterminant = false);

	//����������Ψһ��Ľ����;��󻯼�
	void _RegressReduce();

	//���ؽ����;������
	int _Rank();
};

#endif