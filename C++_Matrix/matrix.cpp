#include "matrix.h"


static int gcd(int a, int b);
static int lcm(int a, int b);

Matrix & Matrix::GetOne(int one)
{
	buf.push_back(one);
	return *this;
}

Matrix & Matrix::ReFlash()
{
	content.push_back(buf);
	buf.clear();
	return *this;
}

void Matrix::ShowMatrix()
{
	for (auto &r : content ) {
		putchar('|');
		for (auto &c: r) {
			printf("%7d", c);
		}
		printf("      |\n");
	}
}

bool Matrix::IsEmpty()
{
	return content.size() == 0;
}

bool Matrix::IsBufEmpty()
{
	return buf.size() == 0;
}

//这个函数的智能水平还有待提高
//感觉流程比较复杂，不知道能不能再拆分一些出来
Matrix & Matrix::RowReduce()
{
	//增广矩阵中未知数数量为列数减一
	const int Xnum = content[0].size() - 1;
	const int Rnum = content.size();
	//到达边界，或者剩余行全为0，则结束
	for (int i = 0; i <Xnum; ++i) {
		
		//判断pivot是否需要交换行位置
		int ReturnRow = CheckPivot(i);
		if ( ReturnRow > 0) {
			RowEx(i, ReturnRow);
		}
		else if (ReturnRow == 0) {
			//全为0直接下一轮
			continue;
		}

		//否则按照正常路径
		for (int j = i + 1; j < Rnum; ++j) {
			//遍历第i列对应的数据
			int pi = GetPivot(i);
			int pj = content[j][i];

			//判断消去行是否为0，是则直接下一轮
			if (pj == 0) {
				continue;
			}

			//计算达到最小公倍数的因子，
			int ps = lcm(pi, pj);
			pi = ps / pi;
			pj = ps / pj;

			//由数学知识，两个因子和原来的数据相乘以后，两行的符号总是相同的
			//使不变的一行前面加上负号即可保证消除
			RowExCP(pj,j,-pi,i);

			//调试代码，注意移除
			//std::cout << std::endl;
			//ShowMatrix();
		}
	}

	//已经化成阶梯型了，下面开始向上化简
	//反向迭代，边界条件有变化
	for (int i = Xnum - 1; i >= 0; --i) {
		Reduceone(i);
		for (int j = i -1; j >= 0; --j) {
			int pi = GetPivot(i);
			int pj = content[j][i];

			int ps = lcm(pi, pj);
			pi = ps / pi;
			pj = ps / pj;

			RowExCP(pj, j, -pi, i);
		}
	}


	return *this;
}

Matrix & Matrix::RowEx(int row1, int row2)
{
	auto &r1 = content[row1];
	auto &r2 = content[row2];
	r1.swap(r2);

	return *this;
}

Matrix & Matrix::RowExC(int C, int row)
{
	auto &r = content[row];
	for (auto & i : r) {
		i = C * i;
	}

	return *this;
}

Matrix & Matrix::RowExCP(int C1, int row, int C2, int crow)
{	
	//被加的一行需要修改原始数据，另一行不要修改
	auto &r = content[row];
	auto cr = content[crow];

	for (auto & i : r) {
		i *= C1;
	}

	for (auto & i : cr) {
		i *= C2;
	}

	for (unsigned int i = 0; i < r.size(); ++i) {
		r[i] += cr[i];
	}

	return *this;
}

int Matrix::GetPivot(int row)
{
	auto &r = content[row];
	for (auto &i : r) {
		if (i != 0) {
			return i;
		}
	}
	return 0;
}

int Matrix::CheckPivot(int row)
{
	const int NotFound = 0;
	const int IsGood = -1;

	if (content[row][row] == 0) {
		for (int i = row + 1; i < content.size(); ++i) {
			if (content[i][row] != 0) {
				return i;
			}
		}
		return NotFound;	
	}
	else {
		return IsGood;		
	}
}

int Matrix::Getb(int row)
{
	int col = content[0].size();
	return content[row][col];
}

void Matrix::Reduceone(int row)
{
	auto &r = content[row];
	int gcdnum = 0;
	//获得一行的全部元素的公因子
	for (const auto &i : r) {
		gcdnum = gcd(i, gcdnum);
	}
	
	for (auto &i : r) {
		i /= gcdnum;
	}
}


bool Matrix::IsRegular()
{	
	//定义空矩阵是规则的
	if (this->IsEmpty())
	{
		return true;
	}

	//如果缓冲区有数据，先刷新缓存区
	if (!this->IsBufEmpty())
	{
		this->ReFlash();
	}

	auto reg = content[0].size();
	for (auto &r : content)
	{
		if (r.size() != reg)
		{
			return false;
		}
	}
	return true;
}



static int gcd(int a, int b)
{
	int r;
	while (b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

static int lcm(int a, int b)
{
	return a*b / gcd(a, b);
}
