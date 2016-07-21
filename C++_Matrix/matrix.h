#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <cstdio>
#include <fstream>

class Matrix
{
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
	int GetPivot(int row);

	//���pivot�Ƿ�Ϊ0
	//����ǣ����ص�һ������0���У���������ڣ�����0
	//������ǣ�����һ������
	int CheckPivot(int row);

	//������������ж�Ӧ�е�b��ֵ
	int Getb(int row);

	//ȥ�������еĹ�����
	void Reduceone(int row);



};

#endif