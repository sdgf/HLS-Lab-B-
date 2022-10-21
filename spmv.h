#ifndef __SPMV_H__
#define __SPMV_H__

#include <ap_axi_sdata.h>
#include <hls_stream.h>

const static int SIZE = 4; // SIZE of square matrix
const static int NNZ = 9; //Number of non-zero elements
const static int NUM_ROWS = 4;// SIZE;
const static int II_com = 3;//for compile time parameter

typedef union {
	unsigned int i;
	float f;
} intfp;
//typedef ap_axiu<32,1,1,1> value_t;
typedef hls::stream<intfp> stream_t;
typedef float DTYPE;
void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
		  DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE]);

#endif // __MATRIXMUL_H__ not defined
