#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

typedef struct matrix{
	int row;
	int column;
	int * head;
}Matrix;

typedef struct configuration{
	int input;
	int output;
}Configuration;

bool InitializeMatrix(Matrix * pmx,int row,int column);

Configuration Matrix_Configuration(Matrix * pmx);

void Get_File_Matrix(Matrix * pmx,const char * filename);

void Get_Stdin_Matrix(Matrix * pmx);

void ShowMatrix(const Matrix * pmx);

void WriteToFile(const Matrix * pmx);

void ToTriangleMattrix(Matrix * pmx);

void Traverse(Matrix * pmx, void (*pfun)(int item));

#endif
