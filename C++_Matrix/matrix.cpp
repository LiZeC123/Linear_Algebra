#include "matrix.h"

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
	
	//���������δ֪������Ϊ������һ
	const int Xnum = content[0].size() - 1;
	const int Rnum = _Rank();

	//δ֪���������ʱ������Ψһ�⣬�Ӷ����л���
	if (Xnum == Rnum) {
		_RowReduce_Only();
	}
	else {
		//����ֻ�Է�0�н���ϵ���Ļ���
		for (int i = 0; i < Rnum; ++i) {
			Reduceone(i);
		}
	}

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
	//���ӵ�һ����Ҫ�޸�ԭʼ���ݣ���һ�в�Ҫ�޸�
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
	//���һ�е�ȫ��Ԫ�صĹ�����
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
	int expand = 1;
	const int Rnum = content.size();
	//��������ͬʱ���㣬���ܱ�֤���鲻Խ��
	for (int i = 0; i < Rnum; ++i) {

		//�ж�pivot�Ƿ���Ҫ������λ��
		int ReturnRow = CheckPivot(i);
		if (ReturnRow > 0) {
			RowEx(i, ReturnRow);
		}
		else if (ReturnRow == 0) {
			//ȫΪ0ֱ����һ��
			continue;
		}

		//����������·��
		for (int j = i + 1; j < Rnum; ++j) {
			//������i�ж�Ӧ������
			int pi = GetPivot(i);
			int pj = content[j][i];

			//�ж���ȥ���Ƿ�Ϊ0������ֱ����һ��
			if (pj == 0) {
				continue;
			}

			//����ﵽ��С�����������ӣ�
			int ps = lcm(pi, pj);
			pi = ps / pi;
			pj = ps / pj;

			//����ѧ֪ʶ���������Ӻ�ԭ������������Ժ����еķ���������ͬ��
			//ʹ�����һ��ǰ����ϸ��ż��ɱ�֤����
			RowExCP(pj, j, -pi, i);

			//��¼�仯���е�������
			expand *= pj;

			//���Դ��룬ע���Ƴ�
			//std::cout << std::endl;
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

void Matrix::_RowReduce_Only()
{
	const int Rnum = _Rank();

	//����������߽������б仯
	for (int i = Rnum - 1; i >= 0; --i) {
		Reduceone(i);
		for (int j = i - 1; j >= 0; --j) {
			int pi = GetPivot(i);
			int pj = content[j][i];

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
	for (unsigned int i = 0; i < content.size(); ++i) {
		if (GetPivot(i) != 0) {
			++rank;
		}
	}
	return rank;
}


bool Matrix::IsRegular()
{	
	//����վ����ǹ����
	if (this->IsEmpty())
	{
		return true;
	}

	//��������������ݣ���ˢ�»�����
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

