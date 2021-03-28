
#include "cabeceras.h"
#include<fstream>
int main()
{

int fila=0;
int columna=0;
double ** imagen = cargarImagen("imagenes/iris.jpg",fila,columna );
	
 

unsigned t0, t1; t0=clock();

double ** mat_or = imagen;
double **mat_gradiente = new double* [fila];
for (int i = 0; i < fila; ++i)
	mat_gradiente[i] = new double[columna];

canny(imagen,mat_gradiente,mat_or, fila,columna , 1,1,1);
adjgamma(mat_gradiente,fila,columna,1.9);
Matrix i4 = nonmaxsup(mat_gradiente,fila, columna, mat_or, fila, columna, 1.5);

int** final=hysthresh(i4, fila,columna,0.23, 0.19);
//detectar_circulo(final,fila,columna,30,60);
//detectar_circulo(final,fila,columna,70,120);


std::ofstream fichero("octave_resultados/img.csv"); 
 for (int i = 0; i < fila; ++i){
 	for (int j = 0; j < columna; ++j){
 		fichero << (final[i][j]) <<","; 
 	}fichero << std::endl; 
}
fichero.close(); 





t1 = clock(); double time = (double(t1-t0)/CLOCKS_PER_SEC);	std::cout << "Execution Time(s):: " << time <<" s__"<< std::endl;







for (int i = 0; i < fila; ++i)
	{
		delete[]  imagen[i];
	}
	delete[] imagen;


	return 0;
}

