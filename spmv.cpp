#include "spmv.h"

void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
		DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE])
{
#pragma HLS TOP name=spmv
#pragma HLS INTERFACE mode=s_axilite port=rowPtr
#pragma HLS INTERFACE mode=s_axilite port=columnIndex
#pragma HLS INTERFACE mode=s_axilite port=values
#pragma HLS INTERFACE mode=s_axilite port=y
#pragma HLS INTERFACE mode=s_axilite port=x
#pragma HLS INTERFACE mode=s_axilite port=return


#pragma HLS ARRAY_PARTITION dim=1 dynamic type=complete variable=rowPtr
#pragma HLS ARRAY_PARTITION dim=1 dynamic type=complete variable=columnIndex

L1: for ( __int8 i = 0; i < NUM_ROWS; i++) {
#pragma HLS LOOP_TRIPCOUNT avg=4 max=4 min=4
		DTYPE y0 = 0;
	L2: for (__int8 k = rowPtr[i]; k < rowPtr[i+1]; k+=7) {
#pragma HLS LOOP_TRIPCOUNT avg=2 max=4 min=0
#pragma HLS unroll factor=7
#pragma HLS PIPELINE
//#pragma HLS dependence variable=y0 direction=RAW type=inter
			DTYPE y_par0 = values[k] * x[columnIndex[k]];

		L3: for (int l=1; l<7; l++){//II_com = 4
				if ( l+k < rowPtr[i+1]){
					y_par0 += values[l+k] * x[columnIndex[l+k]];
				}
			}
			y0 += y_par0;
		}
		y[i] = y0;

	}
}
