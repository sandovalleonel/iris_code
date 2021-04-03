
#include <iostream>
#include <cmath>

Matrix computeDft( double ** mat_input,int row_mat ) 
{
    Matrix mat_output=newDoubleMatrix(row_mat,2);
    int n = row_mat;
    for (int k = 0; k < n; k++) {  
        double sumreal = 0;
        double sumimag = 0;
        for (int t = 0; t < n; t++) { 
            double angle = 2 * PI * t * k / n;
            sumreal +=  mat_input[t][0] * cos(angle) + mat_input[t][1] * sin(angle);
            sumimag += -mat_input[t][0] * sin(angle) + mat_input[t][1] * cos(angle);
        }
        mat_output[k][0] = sumreal;
        mat_output[k][1] = sumimag;
    }
    deleteDoubleMatrix(mat_input,row_mat);
   return mat_output;
}

void computeIDft( double ** mat_input,Matrix &mat_ouput,int row_mat )
{
    Matrix aux_fft = newDoubleMatrix(row_mat,2);

     aux_fft =computeDft(mat_input,row_mat);
    int tam_vec = row_mat;
        
        mat_ouput[0][0]=(aux_fft [0][0] / tam_vec);
        mat_ouput[0][1]=(aux_fft [0][1] / tam_vec);
 
    for (int i = tam_vec - 1; i > 0; --i)
    {   
        mat_ouput[i][0]=(aux_fft [i][0] / tam_vec);
        mat_ouput[i][1]=(aux_fft [i][1] / tam_vec);
    }

    //deleteDoubleMatrix(mat_input,row_mat);

}
