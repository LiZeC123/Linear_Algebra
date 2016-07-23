#pragma once
#include <iostream>

#include "Math_Function.h"

class Fraction
{
public:
	Fraction() = default;
	Fraction(int m, int d) : mem(m), den(d) {};

public:
	Fraction & ShowFraction();

private:
	int mem = 1;		//·Ö×Ó 
	int den = 1;		//·ÖÄ¸ 

	void Reduce();
};
