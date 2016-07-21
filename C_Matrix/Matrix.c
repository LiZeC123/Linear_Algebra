#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
//将数学上的行与列转化为线性的数值 
static int  EdxToEdx(Matrix * pmx,int i,int j);

//在pmx指向的矩阵中，将row指定的一行复制到ptemp指向的数组之中 
static void CopyToTemp(int * ptemp,int row,Matrix * pmx);


bool InitializeMatrix(Matrix * pmx,int row,int column){
	pmx->row    = row;
	pmx->column = column;
	int *ptem;
	ptem = (int *)malloc(row*column*sizeof(int));
	if(ptem == NULL){
		return false;
	}
	pmx->head   = ptem;
	return true;
}

Configuration Matrix_Configuration(Matrix * pmx){
	Configuration con;        				//con 代表configuration 
	FILE * fp_con;
	fp_con = fopen("configuration.txt","r");
	fscanf(fp_con,"[Input] = %d\n",&con.input);
	fscanf(fp_con,"[Output] = %d",&con.output );
	fclose(fp_con); 
	return con;
}

void Get_File_Matrix(Matrix * pmx,const char * filename){
	int * pi = pmx->head;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int a,b;
	FILE * fp_file;
	fp_file = fopen(filename,"r");
	for(a=0;a<ROW;a++){
		for(b=0;b<COLUMN;b++){
			//修改int后，此处需要修改 
			fscanf(fp_file,"%d",pi);
			pi++;
		}
	}	
}

void Get_Stdin_Matrix(Matrix * pmx){
	int * pi = pmx->head;
	int a,b;
	puts("plesse input your Matrix now");
	for(a=0;a<pmx->row;a++){
		for(b=0;b<pmx->column;b++){
			//修改int后，此处需要修改 
			scanf("%d",pi);
			pi++;
		}
	}		
}


void ShowMatrix(const Matrix * pmx){
	int * pi = pmx->head;
	int a=0,b=0;
	for(a=0;a < pmx->row;a++){
		putchar('|');
		for(b=0; b< pmx->column ;b++){
			printf("%7d",*pi);
			pi++;
		}
		printf("      |\n");
	}
}


void WriteToFile(const Matrix * pmx){
	FILE *fp_output;
	fp_output = fopen("output.txt","w");
	
	int * pi = pmx->head;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;	int temp;
	
	int a=0,b=0;
	for(a=0;a<ROW;a++){
		fprintf(fp_output,"|");
		for(b=0;b<COLUMN;b++){
			fprintf(fp_output,"%7d",*pi);
			pi++;
		}
		fprintf(fp_output,"      |\n");
	}
}




void Traverse(Matrix * pmx, void (*pfun)(int item)){
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int * pi = pmx->head;
	int i,j;
	for(i=0;i<ROW;i++){
		for(j=0;j<COLUMN;j++){
			(*pfun)(*pi);
			pi++;
			//使用指针读取数据 
		}
	}
}


void ToTriangleMattrix(Matrix * pmx){
	int each,i,j;
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int * pi = pmx->head; 
	int temp[COLUMN];		//存放用于化简其他行在计算时的临时数组 
	int temp_do;			//存放用于化简其他行的关键元素 
	int temp_done;			//存放被化简的行的关键元素 
	for(each=1;each<=ROW-1;each++){
		for(i=each+1;i<=ROW;i++){
			CopyToTemp(temp,each,pmx);
			temp_do = pi[EdxToEdx(pmx,each,each)];
			temp_done = pi[EdxToEdx(pmx,i,each)];
			
			for(j=1;j<=COLUMN;j++){
				pi[EdxToEdx(pmx,i,j)] = temp_done*temp[j-1]-temp_do*pi[EdxToEdx(pmx,i,j)]; 
			}	
		}
	} 
} 


static int  EdxToEdx(Matrix * pmx,int i,int j){
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int r = (i-1)*COLUMN+(j-1);
	return r;
}


static void CopyToTemp(int * ptemp,int row,Matrix * pmx){
	const int ROW = pmx->row;
	const int COLUMN = pmx->column;
	int * pi = pmx->head;
	int start,end,i;
	start = EdxToEdx(pmx,row,1);
	end   = EdxToEdx(pmx,row,COLUMN);
	for(i=start;i<=end;i++){
		*ptemp = pi[i];
		ptemp++;
	}
}
