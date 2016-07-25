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

	//��վ��������
	Matrix & Clear();





private:
	std::vector<int> buf;
	std::vector<std::vector<int> > content;

	//���������б任
	//��������
	Matrix & RowEx(int row1, int row2);
	//ָ���г��Գ�����
	Matrix & RowExC(int C, int row);
	//ָ������������ϼӵ���һ��
	Matrix & RowExCP(int C1, int row, int C2, int crow);

	//����ָ���е�pivot�������е�һ����0Ԫ�ص�ֵ
	//��ȫΪ0���򷵻�0
	int GetPivot(int row);

	//���pivot�Ƿ�Ϊ0
	//����ǣ����ص�һ������0���У���������ڣ�����0
	//������ǣ�����һ������
	int CheckPivot(int row);

	//������������ж�Ӧ�е�b��ֵ
	int Getb(int row);

	//ȥ�������еĹ�����
	void Reduceone(int row);
	
	//�������ľ��󻯳ɽ�����
	int _RowReduce_Tri(bool IsDeterminant = false);
	//����������Ψһ��Ľ����;��󻯼�
	void _RowReduce_Only();

	//���ؽ����;������
	int _Rank();

	//���ؾ����е�һ��
	std::vector<int> GetCol(int col);

};


#endif