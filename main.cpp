#include "includes.h"
int main(int argc, char const *argv[])
{
	int imgRow,imgCol,xcenter,ycenter,rmin,rmax;

	/* First  step  segmentation*/
	Matrix img=loadImage("img/iris.jpg",imgRow,imgCol);
	Matrix mat_gradient=newDoubleMatrix(imgRow,imgCol);
	Matrix mat_or=newDoubleMatrix(imgRow,imgCol);
	canny(img,mat_gradient,mat_or,imgRow,imgCol,1,1,1);
	adjgamma(img,imgRow,imgCol,1.5);
	Matrix i4=nonmaxsup(mat_gradient,imgRow,imgCol, mat_or,imgRow,imgCol, 1.5);
	IntMatrix final=hysthresh(i4,imgRow,imgCol,0.23, 0.19);

	IntVector pcoor=detectar_circulo(final,imgRow,imgCol,28,75);
	IntVector icoor=detectar_circulo(final,imgRow,imgCol,80,150);

	//printIntMatrix(final,imgRow,imgCol);

	/* Second step normalization*/
	
	Matrix normalise= normaliseiris(img,imgRow,imgCol,pcoor[0],pcoor[1],pcoor[2],icoor[0],icoor[1],icoor[2],631,720);

	/* Third step  feature extraction*/

	/* Fourth step matching*/


	printf("tamaño de la imagen %d %d\n",imgRow,imgCol);
	printf("Ejecución exiosa .....\n");
	deleteDoubleMatrix(img,imgRow);
	deleteDoubleMatrix(mat_gradient,imgRow);
	deleteDoubleMatrix(mat_or,imgRow);
	deleteDoubleMatrix(i4,imgRow);
	deleteIntMatrix(final, imgRow);
	deleteIntVector(pcoor);
	deleteIntVector(icoor);
	return 0;
}