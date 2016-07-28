#pragma once
#include <stdexcept>
#include <string>

class matrix_mismatch : public std::logic_error
{
public:
	matrix_mismatch(const std::string & s) :
		std::logic_error(s) { };

};


