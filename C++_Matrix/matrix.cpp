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

//�������������ˮƽ���д����
//�о����̱Ƚϸ��ӣ���֪���ܲ����ٲ��һЩ����
Matrix & Matrix::RowReduce()
{
	//���������δ֪������Ϊ������һ
	const int Xnum = content[0].size() - 1;
	const int Rnum = content.size();
	//����߽磬����ʣ����ȫΪ0�������
	for (int i = 0; i <Xnum; ++i) {
		
		//�ж�pivot�Ƿ���Ҫ������λ��
		int ReturnRow = CheckPivot(i);
		if ( ReturnRow > 0) {
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
			RowExCP(pj,j,-pi,i);

			//���Դ��룬ע���Ƴ�
			//std::cout << std::endl;
			//ShowMatrix();
		}
	}

	//�Ѿ����ɽ������ˣ����濪ʼ���ϻ���
	//����������߽������б仯
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
	
	for (auto &i : r) {
		i /= gcdnum;
	}
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
