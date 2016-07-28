#include "Matrix.h"
#include "Matrix_Operator.h"

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

Matrix & Matrix::RowReduce()
{
	_RowReduce_Tri();
	_RegressReduce();
	return *this;
}

Fraction Matrix::det()
{
	int expend = _RowReduce_Tri(true);
	int det = 1;
	for (unsigned int i = 0; i < content.size(); ++i) {
		det *= content[i][i];
	}

	return Fraction(det,expend);
}

Matrix & Matrix::Transpose()
{
	Matrix temp;
	for (unsigned int i = 0; i < content[0].size(); ++i) {
		temp.buf = GetCol(i);
		temp.ReFlash();
	}
	content.swap(temp.content);
	return *this;
}

Matrix & Matrix::Clear()
{
	content.clear();
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
	if (C != 0) {
		auto &r = content[row];
		for (auto & i : r) {
			i = C * i;
		}
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
	for (unsigned int i = 0; i < r.size(); ++i) {
		if (r[i] != 0) {
			return i;
		}
	}

	return r.size();
}

int Matrix::CheckPivot(unsigned int doRow, unsigned int col)
{
	const int NotFound = content.size();
	const int IsGood = -1;
	unsigned int i = doRow;

	//大于矩阵返回，直接返回
	if (col >= content.size() || i >= content[0].size()) {
		return IsGood;
	}
	
	if (content[i][col] == 0) {
		for ( ; i < content.size(); ++i) {
			if (content[i][col] != 0) {
				break;
			}
		}
		return i;
	}
	else {
		return IsGood;
	}

}

void Matrix::Reduceone(int row)
{
	auto &r = content[row];
	int gcdnum = 0;
	//获得一行的全部元素的公因子
	for (const auto &i : r) {
		gcdnum = gcd(i, gcdnum);
	}
	
	if (gcdnum != 0) {
		for (auto &i : r) {
			i /= gcdnum;
		}
	}
}

int Matrix::_RowReduce_Tri(bool IsDeterminant)
{
	const unsigned int Rnum = content.size();
	const unsigned int Cnum = content[0].size();

	int expand = 1;
	unsigned int eli_col = 0;

	//遍历每一行，同时控制消去列的位置
	for (unsigned int i = 0; i < Rnum && eli_col < Cnum; ++i,++eli_col) {
		
		//判断pivot是否需要交换行位置
		int ReturnRow = CheckPivot(i, eli_col);
		while (ReturnRow > 0)
		{
			if (ReturnRow < Rnum) {
				//交换行列式位置，结果变号
				expand = -expand;
				RowEx(i, ReturnRow);
			}
			else if (ReturnRow == Rnum) {
				//全部为零，直接开始判断下列的情况
				++eli_col;
			}
			ReturnRow = CheckPivot(i, eli_col);
		}
	
		//遍历第i行下剩余的行
		for (int j = i + 1; j < Rnum && eli_col < Cnum; ++j) {
			
			
			int pi = content[i][eli_col];
			int pj = content[j][eli_col];

			//判断消去行是否为0，是则跳过，开始消去下一行
			if (pj == 0) {
				continue;
			}

			//消去该行前计算达到最小公倍数的因子
			int ps = lcm(pi, pj);
			pi = ps / pi;
			pj = ps / pj;

			//由数学知识，两个因子和原来的数据相乘以后，两行的符号总是相同的
			//使不变的一行前面加上负号即可保证消除
			RowExCP(pj, j, -pi, i);

			//记录变化的行的扩大倍数
			expand *= pj;

			//调试代码，注意移除
			//std::cerr << std::endl;
			//ShowMatrix();
		}
	}

	if (IsDeterminant) {
		return expand;
	}
	else {
		return 1;
	}
}

void Matrix::_RegressReduce()
{
	const int Rnum = _Rank();
	unsigned int elicol = content[0].size() - 1;

	//反向迭代，边界条件有变化
	for (int i = Rnum - 1; i >= 0; --i) {
		Reduceone(i);
		for (int j = i - 1; j >= 0; --j) {
			unsigned int eli_col = GetPivot(i);
			//已经计算过rank，所以不会越界
			int pi = content[i][eli_col];
			int pj = content[j][eli_col];

			//判断消去行是否为0，是则直接下一轮
			if (pj == 0) {
				continue;
			}

			int ps = lcm(pi, pj);
			pi = ps / pi;
			pj = ps / pj;

			RowExCP(pj, j, -pi, i);
		}
	}

}

int Matrix::_Rank()
{
	int rank = 0;
	//先判断是否越界，才能判断这一行的值
	for (unsigned int i = 0;i < content.size() && GetPivot(i) != content[0].size(); ++i) {
		if (content[i][GetPivot(i)] != 0 ) {
			++rank;
		}
	}
	return rank;
}

std::vector<int> Matrix::GetCol(int col)
{
	std::vector<int> ret;
	for (unsigned int i = 0; i < content.size(); ++i) {
		for (unsigned int j = 0; j < content[0].size(); ++j) {
			if (j == col) {
				ret.push_back(content[i][j]);
			}
		}
	}

	return ret;

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

Matrix operator+(Matrix & lmx, Matrix & rmx)
{
	if (!(lmx.content.size() == rmx.content.size() &&
		lmx.content[0].size() == lmx.content[0].size())) {
		throw matrix_mismatch("矩阵不同型");
	}

	Matrix mx;
	for (unsigned int i = 0; i < lmx.content.size(); ++i) {
		for (unsigned int j = 0; j < lmx.content[0].size(); ++j) {
			mx.GetOne(lmx.content[i][j] + rmx.content[i][j]);
		}
		mx.ReFlash();
	}	
	return mx;
}

Matrix operator*(int C, Matrix & rmx)
{	
	Matrix mx;
	for (auto &r : rmx.content) {
		for (auto &i : r) {
			mx.GetOne(C*i);
		}
		mx.ReFlash();
	}

	return mx;
}

Matrix operator-(Matrix & lmx, Matrix & rmx)
{
	return lmx + (-1 * rmx);
}


Matrix operator*(Matrix & lmx, Matrix & rmx)
{
	if (lmx.content[0].size() != rmx.content.size()) {
		throw matrix_mismatch("矩阵形式不匹配");
	}

	Matrix mx;
	for (unsigned int i = 0; i < lmx.content.size(); ++i) {
		for (unsigned int j = 0; j < rmx.content[0].size(); ++j) {
			mx.GetOne(dot(lmx.content[i], rmx.GetCol(j)));
		}
		mx.ReFlash();
	}
	return mx;
}