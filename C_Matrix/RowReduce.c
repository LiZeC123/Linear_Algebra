#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Matrix Rc;
	int  row,column;
	printf("How many unknown number does the matrix have:");
	scanf("%d",&row);
	column=row+1;
	
	//初始化 
	if(!InitializeMatrix(&Rc,row,column)){
		puts("The memory is full now.");
		system("pause");
		exit(1);
	}
	Configuration con;
	con = Matrix_Configuration(&Rc);
	
	//按照配置文件选择读取方式 
	if(con.input == 1){
		Get_File_Matrix(&Rc,"source.txt");
	}
	else{
		Get_Stdin_Matrix(&Rc);
	}
	
	//显示当前矩阵 
	puts("There is the matrix you input:");
	ShowMatrix(&Rc);
	
	//转化成三角形方程
	ToTriangleMattrix(&Rc);
	
	//按照配置文件输出
	if(con.output  == 10){
		puts("there is the answer:");
		ShowMatrix(&Rc);	
	} 
	else if(con.output  == 01){   //注意此处01，即表示八进制数 1 
		WriteToFile(&Rc);
	}
	else if(con.output == 11){
		puts("there is the answer:");
		ShowMatrix(&Rc);
		WriteToFile(&Rc);
	}
	return 0;
}
