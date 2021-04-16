#include "includes.h"
#include "feature_extract/gaborconvolve.h"
#include <iostream>
#include <vector>
#include <dirent.h>
#include <string>
#include <cstring>
int main(int argc, char const *argv[])
{
	unsigned t0, t1; t0=clock();
	int imgRow,imgCol;//,xcenter,ycenter,rmin,rmax;

	/* First  step  segmentation*/
	//char * name_file ;
 


	DIR *dir; struct dirent *diread;
    const char* path ="/home/leonel/Descargas/CASIA-Iris-Lamp/005/R/";
            
    if ((dir = opendir(path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {

            std::string name_file = diread->d_name;
            if (name_file != "." && name_file != "..")
            {

            std::string val=path+name_file; 
    Matrix img_general=loadImage(val.c_str(),imgRow,imgCol);
        // std::cout<<val<<std::endl;  
   	Matrix img=loadImage(val.c_str(),imgRow,imgCol);
	Matrix mat_gradient=newDoubleMatrix(imgRow,imgCol);
	Matrix mat_or=newDoubleMatrix(imgRow,imgCol);
	canny(img,mat_gradient,mat_or,imgRow,imgCol,1,1,1);
	adjgamma(img,imgRow,imgCol,1.5);
	Matrix i4=nonmaxsup(mat_gradient,imgRow,imgCol, mat_or,imgRow,imgCol, 1.5);
	IntMatrix final=hysthresh(i4,imgRow,imgCol,0.23, 0.19);
	int r_min = 28;
	int r_max = 75;
	IntVector pcoor=detectar_circulo(final,imgRow,imgCol,33,54);
	int x=20;
	int y=240;
	

	//Matrix normalise= normaliseiris(img_general,imgRow,imgCol,pcoor[0],pcoor[1],pcoor[2],pcoor[0],pcoor[1] ,2*pcoor[2],x,y);


	//gaborconvolve(normalise,x,y,1,2,2,2);


	//printf("tamaño de la imagen %d %d\n",imgRow,imgCol);
	//printf("Ejecución exiosa .....\n");
	deleteDoubleMatrix(img,imgRow);
	deleteDoubleMatrix(img_general,imgRow);
	deleteDoubleMatrix(mat_gradient,imgRow);
	deleteDoubleMatrix(mat_or,imgRow);
	deleteDoubleMatrix(i4,imgRow);
	deleteIntMatrix(final, imgRow);
	deleteIntVector(pcoor);
	
            }
        }
        closedir (dir);
    }



	/* Second step normalization*/

	
	//


	//
	/* Third step  feature extraction*/

	/* Fourth step matching*/



	t1 = clock(); double time = (double(t1-t0)/CLOCKS_PER_SEC);	std::cout << "Execution Time(s):: " << time <<" s__"<< std::endl;


	return 0;
}