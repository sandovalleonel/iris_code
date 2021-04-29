#include "includes.h"
#include <iostream>
#include <fstream>
void nombre_img(const char  *name_img){
    std::ofstream fichero("fichero.log",std::ios_base::app);
    fichero << name_img <<std::endl;
    fichero.close();
}
int main(int argc, char const *argv[])
{   unsigned t0, t1; t0=clock(); 
	  int contador = 0;
      int contador_reseteo=0;
    DIR *dir;
    struct dirent *diread;
    const char *path = "/home/leonel/Documentos/casia_datos/train_1/";

    if ((dir = opendir(path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {

            std::string name_file = diread->d_name;
            
            if (name_file != "." && name_file != "..") {

                nombre_img(name_file.c_str());

                std::string label_user = name_file.substr(2,3);
                if (name_file.substr(5,1) == "R")   label_user = label_user+"1";
                if (name_file.substr(5,1) == "L")   label_user = label_user+"2";

                int id_user = std::stoi(label_user);
                

                std::string val=path+name_file;
                int imgRow,imgCol;
                float *auximg;
                Matrix img3;
                loadImage2(val.c_str(),imgRow,imgCol,auximg,img3);
                int outrow=imgRow,
                        outcol=imgCol;
                scaling(outrow,outcol,400);
                Matrix img=imgResize(auximg,imgRow,imgCol,outrow,outcol);
                Matrix mat_gradient=newDoubleMatrix(outrow,outcol);
                Matrix mat_or=newDoubleMatrix(outrow,outcol);
                canny(img,mat_gradient,mat_or,outrow,outcol,1,1,1);
                adjgamma(mat_gradient,outrow,outcol,2);           //gama casia 2.2  //4 //3
                Matrix i4=nonmaxsup(mat_gradient,outrow,outcol, mat_or,outrow,outcol, 1.5); //original 1.5 //2
                
                IntMatrix final=hysthresh(i4,outrow,outcol,0.23,0.19); 

                int r_min = 55;
                int r_max = 65;
                
                IntVector pcoor=detectar_circulo(final,outrow,outcol,r_min,r_max,0.1);
                //printf("%s %d\n","**************",pcoor[2] );
                /* escalar el radio*/
                //int raux=pcoor[2];
                //printf("%d\n",raux );

                int rx, ry,r;
                resizeExternalCoor(rx,ry,r,imgCol,outcol,imgRow,outrow,pcoor);
                 
                //---------------
                
                deleteDoubleMatrix(img,outrow);
                deleteDoubleMatrix(mat_gradient,outrow);
                deleteDoubleMatrix(mat_or,outrow);
                deleteDoubleMatrix(i4,outrow);
                deleteIntMatrix(final,outrow);

                int fila = pcoor[1];//x
                int columna = pcoor[0];//y
                int radio = pcoor[2];//r
                int fil_col = radio * 2;
                scaling(outrow,outcol,400);
                Matrix img2=imgResize(auximg,imgRow,imgCol,outrow,outcol);//Matrix img2=loadImage(val.c_str(),imgRow,imgCol);//llamar  cargar imagen en double normal
                Matrix mat_ojo = newDoubleMatrix(fil_col,fil_col);
                int conti = 0;
                int contj = 0;
                //gregar condicion fil-radio < 0...inicia.i=0
                //gregar condicion col-radio < 0...inicia.j=0
                
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
                canny(mat_ojo,mat_gradient2,mat_or2,fil_col,fil_col,1,1,1);
                adjgamma(mat_gradient2,fil_col,fil_col,4);  //2.1 detecta borde exterior celular         //gama casia 2.2
                Matrix i42=nonmaxsup(mat_gradient2,fil_col,fil_col, mat_or2,fil_col,fil_col, 1.5); //original 1.5
                IntMatrix final2=hysthresh(i42,fil_col,fil_col,0.34, 0.27); // original 0,23 0,19


                // writeImage(final,outrow,outcol);
                //----------------------

                int r_min2 = round(radio*0.25);//radio15% //radio*0.1;//10;//33//28
                int r_max2 = radio-round(radio*0.2);//radioexterior//25;//54//75
                IntVector pcoor2=detectar_circulo(final2,fil_col,fil_col,r_min2,r_max2,0.20);

                int rx2,ry2,r2;
                resizeInternalCoor( rx2,ry2,r2,imgCol,outcol,imgRow,outrow,pcoor2,columna, fila,radio); // redimensionar a escala original

                //Matrix img3=loadImage(ruta,imgRow,imgCol);
                /*paintCircle(img3,imgRow, imgCol, rx, ry,rx2,ry2, r, r2);
                 std::string name2 = name_file; //std::to_string();
                 int **aux2=double2Int(img3,imgRow,imgCol);
                 writeImageJPG(aux2,imgRow,imgCol,name2.c_str());*/
                 

                //-----------
                //fase de normalizacion
                int nrow=20,nrcol=240;
                Matrix normalize=normaliseiris(img3,imgRow,imgCol,rx,ry,r,rx2,ry2,r2,nrow,nrcol);
                //----fin fase

                //-----fase extraccion de caracteristicas- codificacion
                gaborconvolve(normalize,nrow,nrcol,1,18,1,0.5,id_user);
                //-----------------------------------------------------

                // deleteIntMatrix(aux2,imgRow);


                deleteDoubleMatrix(normalize,nrow);
                delete[]auximg;
                auximg=nullptr;
                deleteIntVector(pcoor2);
                deleteIntVector(pcoor); 
                deleteDoubleMatrix(img3,imgRow);
                deleteDoubleMatrix(mat_ojo,fil_col);
                deleteDoubleMatrix(img2,fil_col);
                deleteDoubleMatrix(mat_gradient2,fil_col);
                deleteDoubleMatrix(mat_or2,fil_col);
                deleteDoubleMatrix(i42,fil_col);
                deleteIntMatrix(final2,fil_col);

            contador++;
            contador_reseteo++;

                if(contador_reseteo==100){std::cout<<"Total: "<<contador<<" de 4000"<<std::endl; contador_reseteo=0;}



            }
        }
    }
   t1 = clock();double time = (double(t1-t0)/CLOCKS_PER_SEC);printf("tiempo: %lf (s) \n",time); 
	return 0;
}