#include <stdio.h>
#include "spmv.h"

int main(){
	int fail = 0;
	DATA_TYPE M[SIZE][SIZE] = {{3,4,0,0},{0,5,9,0},{2,0,3,1},{0,4,0,6}};
	DATA_TYPE x[SIZE] = {1,2,3,4};
	DATA_TYPE y_sw[SIZE] = {11,37,15,32};
	DATA_TYPE values[] = {3,4,5,9,2,3,1,4,6};
	u32 columnIndex[] = {0,1,1,2,0,2,3,1,3};
	u32 rowPtr[] = {0,2,4,7,9};
	u32 rows[] = {2,2,3,2};
	DATA_TYPE y[SIZE];

	//spmv(rowPtr, columnIndex, values, y, x);
	spmv_accel(values, columnIndex, rows, x, y, 4, 4, 9);
	//spvm_kernel(values, cols, rows, x_local, y, row_size, col_size, data_size);
	//matrixvector(M, y_sw, x);

	for(int i = 0; i < SIZE; i++)
		if( y_sw[i] != y[i])
			fail = 1;

	if(fail == 1)
		printf("FAILED\n");
	else
		printf("PASS\n");

	return fail;
}
