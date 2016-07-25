#include "Math_Function.h"

int gcd(int a, int b)
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

int lcm(int a, int b)
{
	return a*b / gcd(a, b);
}

int dot(std::vector<int> v1, std::vector<int> v2)
{
	int dot = 0;
	if (v1.size() == v2.size()) {
		for (unsigned int i = 0; i < v1.size(); ++i) {
			dot += (v1[i] * v2[i]);
		}
	}
	return dot;
}