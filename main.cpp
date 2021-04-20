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
    const char* path ="/home/leonel/iris_code/img/";
            
    if ((dir = opendir(path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {

            std::string name_file = diread->d_name;
            if (name_file != "." && name_file != "..")
            {

            std::string val=path+name_file; 

int imgRow,imgCol;//,xcenter,ycenter,rmin,rmax;
	float *auximg=loadImage2(val.c_str(),imgRow,imgCol);
	int outrow=imgRow,
	    outcol=imgCol;
    scaling(outrow,outcol,400);
    Matrix img=imgResize(auximg,imgRow,imgCol,outrow,outcol);

	/* First  step  segmentation*/
	Matrix mat_gradient=newDoubleMatrix(outrow,outcol);
	Matrix mat_or=newDoubleMatrix(outrow,outcol);
	canny(img,mat_gradient,mat_or,outrow,outcol,1,1,1);
    adjgamma(mat_gradient,outrow,outcol,1.5);           //gama casia 2.2

	Matrix i4=nonmaxsup(mat_gradient,outrow,outcol, mat_or,outrow,outcol, 1.5); //original 1.5

	//WritwResult2(i4,outrow,outcol);
	IntMatrix final=hysthresh(i4,outrow,outcol,0.23, 0.19); // original 0,23 0,19

   WritwResult(final,outrow,outcol);
   //writeImage(final,outrow,outcol);

	int r_min = 10;//10;//33//28
	int r_max = 100;//25;//54//75
	IntVector pcoor=detectar_circulo(final,outrow,outcol,r_min,r_max);


	/* Second step normalization*/
	//Matrix normalise= normaliseiris(img_general,imgRow,imgCol,pcoor[0],pcoor[1],pcoor[2],pcoor[0],pcoor[1] ,2*pcoor[2],x,y);


	//gaborconvolve(normalise,x,y,1,2,2,2);


   
	
            }
        }
        closedir (dir);
    }





	



	//
	/* Third step  feature extraction*/

	/* Fourth step matching*/



	t1 = clock(); double time = (double(t1-t0)/CLOCKS_PER_SEC);	std::cout << "Execution Time(s):: " << time <<" s__"<< std::endl;


	return 0;
}