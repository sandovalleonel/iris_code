extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
}


int sizeImgRow,sizeImgCol; 

double **intMatrix(int rows, int cols){ 
double **matrix=new double *[rows];
for (int i = 0; i < rows; ++i)
{
matrix[i]=new double[cols];
}

return matrix;
} 
double **cargarImagen(char const *nombre_img, int &row,int &col){

int n;
unsigned char *data = stbi_load(nombre_img, &sizeImgCol, &sizeImgRow, &n, 1);
row=sizeImgRow;
col=sizeImgCol;
double **img=intMatrix(sizeImgRow,sizeImgCol);
int cont=0;

for (int i=0;i<sizeImgRow;i++){
for (int j=0;j<sizeImgCol;j++){ 
*(*(img+i)+j)=double(*(data+cont));
cont++;
}
}

stbi_image_free(data);

return img;

} 