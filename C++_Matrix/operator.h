#pragma once
#include "matrix.h"
Matrix operator+(Matrix & lmx, Matrix & rmx);

Matrix operator-(Matrix & lmx, Matrix & rmx);

Matrix operator*(Matrix & lmx, Matrix & rmx);

Matrix operator*(int C, Matrix & rmx);