//#include "aplicar_fft_ifft.h"
/*
ingresar la matriz im columnas par
*/
void gaborconvolve(double **im,int row_im,int col_im,int nscale,double minWaveLength,double mult,double sigmaOnf)
{

int ndata = col_im;

///plantilla
int length = col_im * 2 * nscale;
double** plantilla = newDoubleMatrix(row_im,length);

double* logGabor = newDoubleVector(ndata);
int tam_radius = (ndata / 2);

double wavelength = minWaveLength;


for (int z = 1; z <= nscale; ++z)
{
	double fo = 1.0/wavelength;

	for (int i = 1; i <= tam_radius; ++i)
	{
			double aux_data=double(ndata);
			double radius=(i/aux_data);

			double aux1 = log(radius/fo);
			double aux2 = (-1*pow(aux1,2));
			double aux3 = pow(log(sigmaOnf),2);

			logGabor[i] = exp( aux2 / (2 * aux3)); 
	}

///apliar fft fourier*****************************************************************

double ** H1 = newDoubleMatrix(row_im,col_im);
double ** H2 = newDoubleMatrix(row_im,col_im);
double vec_iift[col_im][2];


for (int i = 0; i < row_im; ++i){
	for (int j = 0; j < col_im; ++j){
		double sumreal = 0;
      double sumimag = 0;

      for (int t = 0; t < col_im; t++) { 
            double angle = 2 * PI * t * j / col_im;
            sumreal +=  im[i][t] * cos(angle);
            sumimag += -im[i][t] * sin(angle);
      }
      vec_iift[j][0]=sumreal * logGabor[j];
      vec_iift[j][1]=sumimag * logGabor[j];

	}

	///inversa fourier ifft
	for (int j = 0; j < col_im; ++j){
	double sumreal = 0;
   double sumimag = 0;

      for (int t = 0; t < col_im; t++) { 
          double angle = 2 * PI * t * j / col_im;
          sumreal +=  vec_iift[t][0] * cos(angle) +vec_iift[t][1] * sin(angle);
          sumimag += -vec_iift[t][0] * sin(angle) +vec_iift[t][1] * cos(angle);
          //printf("%lf %lf\n",sumreal,sumimag );
        }
        //crear matriz logica
      if (sumreal>0)
			sumreal=1;
		else
			sumreal=0;

        if (sumimag>0)
			sumimag=1;
		else
			sumimag=0;
		//cargando matriz logica de reales e imaginarios
      if (j == 0)
      {	
       	H1[i][j] = sumreal;
        	H2[i][j] = sumimag;
      }else{
        	H1[i][col_im - j] = sumreal;
        	H2[i][col_im - j] = sumimag;

      }

	
	}

}

    wavelength = wavelength * mult;
//***********************************************************



//___encode
int ja=0,jax=0; 
for (int i = 0; i <row_im ; ++i)
		{
			for (int j = 0; j < col_im; j++)
			{
				ja=2*nscale*j;
				jax=ja+(2*z)-1;
				ja=ja+2*z;
				plantilla[i][jax-1] = H1[i][j];//real 0,2,4,6
				plantilla[i][ja-1] = H2[i][j];//img 1,3,5,7	

			}

		}


//__encode	





}



///imprecion de la plantilla

int contador = 1;
printf("2\t");
for (int i = 0; i < row_im; ++i)
{
	for (int j = 0; j <length; ++j)	{

		//if (int(plantilla[i][j]) == 1)
			printf("%d:%.0f\t",contador , plantilla[i][j]);

	contador++;
		
	}
}printf("\n");


}