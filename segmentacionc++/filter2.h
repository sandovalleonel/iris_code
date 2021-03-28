#include <iostream>

typedef double **Matrix;

Matrix doubleMatrix(int row, int col){
	Matrix vect=new double*[row];
	for (int i = 0; i < row; ++i)
	{
		vect[i]=new double[col];
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j= 0; j < col; ++j)
		{
			vect[i][j]=0;
		}
	}
return vect;

}

int** enteroMatrix(int row, int col){
	int** vect=new int*[row];
	for (int i = 0; i < row; ++i)
	{
		vect[i]=new int[col];
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j= 0; j < col; ++j)
		{
			vect[i][j]=0;
		}
	}
return vect;

}
 
double convulse(Matrix img, Matrix gaussian,int i,int j,int length){
	double sum=0.0;
	int rowG=0,colG=0;
		for (int row = i; row < length+i; row++)
	{
		for (int col = j; col < length+j; col++)
		{
			sum=sum+(img[row][col]*gaussian[rowG][colG]);	
			colG++;

		}
		colG=0;
		rowG++;
	}
	
	return sum;    
}

Matrix filter2(Matrix img, Matrix gauss, int imgRows,int imgCols,int length){
	 int padding=(length/2)*2;
	 int index=length/2;

	Matrix aux=doubleMatrix(imgRows+padding,imgCols+padding);
	Matrix result=doubleMatrix(imgRows,imgCols);
         
		 for (int i = index; i < imgRows+index; ++i)
		 {
		 	for (int j = index; j < imgCols+index; ++j)
		 	{ 	
		 		aux[i][j]=img[i-index][j-index];
			
		 	}
		
		 }

	      for (int i = 0; i <=(imgRows+padding)-length; ++i)
	      {
	      	for (int j = 0; j <=(imgCols+padding)-length; ++j)
	      	{
	    		
	     		 result[i][j]=convulse(aux,gauss,i,j,length);
	     	}
	    	
	     }
	  return result ;

}