#include "Fraction.h"


Fraction & Fraction::ShowFraction()
{
	Reduce();
	if (den == 1) {
		std::cout << mem << std::endl;
	}
	else if (den == -1) {
		std::cout << -mem << std::endl;
	}
	else {
		std::cout << mem << std::endl;
		std::cout << "-" << std::endl;
		std::cout << den << std::endl;
	}

	return *this;
}

void Fraction::Reduce()
{
	int gcdnum = gcd(mem, den);
	mem /= gcdnum;
	den /= gcdnum;
}
