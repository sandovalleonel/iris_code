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
	int imgRow,imgCol;
	/* First  step  segmentation*/
 

	int name_cont = 1;
	DIR *dir; struct dirent *diread;
    const char* path ="/home/leonel/iris_code/img/";
            
    if ((dir = opendir(path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {

            std::string name_file = diread->d_name;
            if (name_file != "." && name_file != "..")
            {

            	std::string val=path+name_file; 

				int imgRow,imgCol;
				float *auximg=loadImage2(val.c_str(),imgRow,imgCol);
				int outrow=imgRow,outcol=imgCol;
			    scaling(outrow,outcol,400);
			    Matrix img=imgResize(auximg,imgRow,imgCol,outrow,outcol);
			    //Matrix img=loadImage(val.c_str(),imgRow,imgCol);
				/* First  step  segmentation*/
				Matrix mat_gradient=newDoubleMatrix(outrow,outcol);
				Matrix mat_or=newDoubleMatrix(outrow,outcol);
				canny(img,mat_gradient,mat_or,outrow,outcol);
			    adjgamma(mat_gradient,outrow,outcol,2);  //2.1 detecta borde exterior celular         //gama casia 2.2
				Matrix i4=nonmaxsup(mat_gradient,outrow,outcol, mat_or,outrow,outcol, 1.7); //original 1.5
				IntMatrix final=hysthresh(i4,outrow,outcol,0.34, 0.27); // original 0,23 0,19

	
				std::string name = std::to_string(name_cont)+".jpg";
			   	//writeImage(final,outrow,outcol,name.c_str());
			   
			   //abel img 10 30-30 80
				int r_min = 11;//10;//33//28
				int r_max = 40;//25;//54//75
				//printf("%s\n","cooerdenadas circulo exterior");
				IntVector pcoor=detectar_circulo(final,outrow,outcol,r_min,r_max,0.1);

				/***************/

////////////////////////////////////////volver a escala real
/*				int fila_400 = pcoor[1];
				int columna_400 = pcoor[0];
				int radio_400 = pcoor[2];

float auxx = (fila_400 * 100)/outrow;	
float x = imgRow * (auxx/100);

float auxy = (columna_400 * 100)/outcol;
float y = imgCol *(auxy/100);



float auxr = (outrow * 100)/imgRow;
float r = (radio_400 * 100)/auxr;

printf("x %lf  y %lf  r %lf\n",x,y,r);*/

int y1 = reestablecer_escala_x_y(pcoor[1],outrow,imgRow);
int x1 = reestablecer_escala_x_y(pcoor[0],outcol,imgCol);
int r1 = reestablecer_escala_radio(pcoor[2],outrow,imgRow);
//printf("%s\n",name_file);
std::cout<<name_file<<std::endl;
printf("externo x=%d  y=%d  r=%d\n",x1,y1,r1);
///////////////////////////////////////////

				deleteDoubleMatrix(img,outrow);
				deleteDoubleMatrix(mat_gradient,outrow);
				deleteDoubleMatrix(mat_or,outrow);
				deleteDoubleMatrix(i4,outrow);
				deleteIntMatrix(final,outrow);
				

				int fila = pcoor[1]*2;//x
				int columna = pcoor[0]*2;//y
				int radio = pcoor[2]*2;//r
				int fil_col = radio * 2; 
				scaling(outrow,outcol,800);
				 Matrix img2=imgResize(auximg,imgRow,imgCol,outrow ,outcol);//Matrix img2=loadImage(val.c_str(),imgRow,imgCol);//llamar  cargar imagen en double normal
				Matrix mat_ojo = newDoubleMatrix(fil_col,fil_col);	
				int conti = 0;
				int contj = 0;
				for (int i = fila-radio; i < fila+radio; ++i)
				{
					for (int j = columna-radio; j < columna+radio; ++j)
					{
						mat_ojo[conti][contj] = img2[i][j];
						contj++;
					}contj=0;conti++;
				}
				
				Matrix mat_gradient2=newDoubleMatrix(fil_col,fil_col);
				Matrix mat_or2=newDoubleMatrix(fil_col,fil_col);
				canny(mat_ojo,mat_gradient2,mat_or2,fil_col,fil_col);
			    adjgamma(mat_gradient2,fil_col,fil_col,4.9);  
				Matrix i42=nonmaxsup(mat_gradient2,fil_col,fil_col, mat_or2,fil_col,fil_col, 1.6); 
				IntMatrix final2=hysthresh(i42,fil_col,fil_col,0.34, 0.27); 

			   std::string name2 = std::to_string(name_cont+100)+".jpg";
			   writeImage(final2,fil_col,fil_col,name2.c_str());

			   	int r_min2 = round(radio*0.25);//radio15% //radio*0.1;//10;//33//28
				int r_max2 = radio-round(radio*0.2);//radioexterior//25;//54//75
				IntVector pcoor2=detectar_circulo(final2,fil_col,fil_col,r_min2,r_max2,0.20);
				//std::cout<<"radio interio x "<<pcoor2[0]<<"  y "<<pcoor2[1]<<"  r "<<pcoor2[2]<<std::endl;
			  //68 73 24--img2 radio interno
			  //550  y 421  r 97 radio externo escala real


				int y2 = reestablecer_escala_x_y((fila-radio)+pcoor2[1],outrow,imgRow);
				int x2 = reestablecer_escala_x_y((columna-radio)+pcoor2[0],outcol,imgCol);
				int r2 = reestablecer_escala_radio(pcoor2[2],outrow,imgRow);
				printf("interno  x2=%d  y2=%d  r2=%d\n",x2,y2,r2);

				/*************/
   





		name_cont++;




delete[]auximg;
deleteDoubleMatrix(mat_ojo,fil_col);
deleteDoubleMatrix(img2,fil_col);
deleteDoubleMatrix(mat_gradient2,fil_col);
deleteDoubleMatrix(mat_or2,fil_col);
deleteDoubleMatrix(i42,fil_col);
deleteIntMatrix(final2,fil_col);


            }
        }
        closedir (dir);
    }





	




	t1 = clock(); double time = (double(t1-t0)/CLOCKS_PER_SEC);	std::cout << "Execution Time(s):: " << time <<" s__"<< std::endl;


	return 0;
}