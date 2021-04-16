
#include "fft.h"
double ** aplicar_fft_ifft(double** im,int row_im,int col_im,double* filter)
{
	double ** signal = newDoubleMatrix(col_im,2);
	double ** imagefft = newDoubleMatrix(col_im,2);
	double ** result = newDoubleMatrix(col_im,2);

	double ** result_out = newDoubleMatrix(row_im,col_im*2);

	
	for (int i = 0; i < row_im; ++i){

		for (int j = 0; j < col_im; ++j)
		{
			signal[j][0] = im[i][j] * filter[j];///(imagefft .* filter);ahorra otro for verificar los resultados de la matriz final
			signal[j][1] = 0;

		}
		
		computeDft(signal,imagefft,col_im);
		for (int j = 0; j < col_im; ++j)
		{
			imagefft[j][0]=imagefft[j][0]*filter[j];
			imagefft[j][1]=imagefft[j][0]*filter[j];
		}
		computeIDft(imagefft,result,col_im);
		
		for (int j = 0; j < col_im; ++j)
		{	
			result_out[i][j] = result[j][0];
			result_out[i][j+col_im] = result[j][1]; 
		}

	}
	
	return result_out;



}