#include "gaborconvolve.h"
#include "double_functions.h"
#include "int_functions.h"
void gaborconvolve(double **polar_array,double** noise_array,row_im,int col_im,int nscale,double minWaveLength,double mult,double sigmaOnf)
{
	//gaborconvolve(double **im,row_im,int col_im,int nscale,double minWaveLength,double mult,double sigmaOnf)

	int length = col_im*2*nscales;
	int **  template = newIntMatrix(row_im,length2);
	int length2 = col_im;

	int h[row_im];
	for (int i = 0; i < row_im; ++i)
		h[i] = i + 1;

	int **  mask = newIntMatrix(row_im,length2);

	for (int z = 0; z < nscale; ++z)
	{
		/* code */
	}

}
