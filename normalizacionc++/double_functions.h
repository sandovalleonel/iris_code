/*
** Universidad Politécnica Salesiana
** Ingeniería de Sistemas
** Autores: Farinango Abel
**			Sandoval Leonel
** Última modificación 2021
*/

#include <vector>
#include <fstream>
#include <iostream>
typedef double **Matrix;
typedef double *Vector;

void deleteDoubleMatrix(Matrix mat, int row){
	/*
	** Mat: matriz de tipo double que va ser liberado de memoria.
	** row: número de filas que tiene la matriz
	** Nota: Esta función libera la memoria ocupada por el apuntador.
	*/
	for (int i = 0; i < row; ++i)
	{
		delete[]mat[i];
	}

	delete[]mat;
}
void deleteDoubleVector(Vector vect){
	/* 
	** vect: vector puntero de tipo double
	** Esta función libera memoria del apuntador tipo vector
	*/
	delete[] vect;
}

Vector newDoubleVector(int length,double value=0){
	/*
	** length: tamaño del vector a crear
	** value: valor con el que se inicializa el vector (opcional, defarult 0)
	** Nota: Esta función crea un vector apuntador de tipo double
	*/
	Vector vect=new double[length];
	for (int i = 0; i < length; ++i)
	{
		vect[i]=value;
	}

	return vect;
}

Vector fillDoubleVector(int start, int end){
	/*
	** start: valor inicial
	** end: valor final
	** Nota: esta función retorna un vector double llenado con los valores dentro de rango start - end
	*/
	int length=end-start;
	double cont=start;
	Vector vect=newDoubleVector(length+1);
	for (int i = 0; i <=length; ++i)
	{
		vect[i]=cont;
		cont++;
	}
	return vect;
}

Matrix newDoubleMatrix(int row, int col, double value=0){
	/*
	** row: número de filas de la matriz
	** col: número de columnas de la matriz
	** value (opcional): valor con la que se inicializa, por defecto 0
	** Nota: Esta funcion devuelve 
	*/
	Matrix vect=new double*[row];
	for (int i = 0; i < row; ++i)
	{
		vect[i]=new double[col];
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j= 0; j < col; ++j)
		{
			vect[i][j]=value;
		}
	}
return vect;

}
 
double convulse(Matrix img, Matrix gaussian,int i,int j,int length){
	/*
	** img: Matriz con los datos de la imagen
	** gaussian: Matriz con el kernel gaussiano
	** i: Indice de donde va ha recorrer la matriz de imagen(fila)
	** j: Indice de donde va ha recorrer la matriz de imagen(columnas)
	** length: tamaño del kernel.
	** Nota: Esta función devuelve el valor de la convulcion.
	*/
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
     /*
     ** img: Matriz de imagen al que se le va a aplicar el filtro
     ** gauss: Matriz filtro (gaussian) "KERNEL"
     ** imgRows: Tamaño de filas de la matriz de imagen(img)
     ** imgCols: Tamaño de columnas de la matriz de iamgen (img)
     ** length: tamaño de la matriz gauss(kernel)
     ** Nota: Esta función devuelve la matriz de imagen aplicada el filtro gaussiano
     */  
	int padding=(length/2)*2;
	int index=length/2;
	Matrix aux=newDoubleMatrix(imgRows+padding,imgCols+padding);
	Matrix result=newDoubleMatrix(imgRows,imgCols);
         
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
	     deleteDoubleMatrix(aux,imgRows+padding);

	  return result ;

}

Matrix transpose(Matrix mat, int sizeRow, int sizeCol){
	/*
	** mat: matriz de datos a transponerse
	** siseRow: número de filas de la matriz(mat)
	** sizeCol: número de columnas de la matriz(mat)
	** Nota: esta función devuelve una matriz transpuesta
	*/
	Matrix trans=newDoubleMatrix(sizeCol, sizeRow);
	for (int i = 0; i < sizeRow; ++i)
	{
		for (int j = 0; j < sizeCol; ++j)
		{
			trans[j][i]=mat[i][j];
		}
	}
return trans;
}

Vector diff(Vector vect, int length){
	/*
	** vect: Vector que contiene los datos
	** length: tamaño del vector
	** Nota: esta función retorna un vector(double) con los valores de la diferencia 
	**       entre los valores del vector original
	*/
	Vector  result=newDoubleVector(length);
	double aux=0.0;
	for (int i = 0; i <length-1; ++i)
	{
		aux=(vect[i+1]-vect[i]);
		result[i]=aux;
	}

	return result;
}


// Funciones temporales solo para test 
void printMatrix(Matrix mat, int row, int col){
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			printf("%f ", mat[i][j]);
		}
		printf("\n");
	}
	deleteDoubleMatrix(mat,row);
}

void printVector(Vector v,int length){
	for (int i = 0; i < length; ++i)
	{
		printf("%lf\n",v[i] );
	}

}
// void printResult(Matrix mat){
// 	std::ofstream fichero("test.csv");
// 	     for (int i = 0; i < int(mat.size()); ++i)
// 	     {
// 	     	for (int j = 0; j < int(mat[0].size()); ++j)
// 	     	{
// 	     		fichero << mat[i][j] <<",";
// 	     	}
// 	     	fichero << std::endl;
// 	     }
		 
// 		 mat.clear();
// 		printf("Impresion finalizado ......");
//         fichero.close();
// }
