void detectar_circulo(int** matimg,int numer_filas,int numero_columnas,int minr,int maxr){
	
int recortex = numero_columnas * 0.25;//opcional reducir columanas o dejar recortex=0;
int recortey = numer_filas * 0.25;   //opcional reducir filas o dejar recortey=0;
int dimZ = int(maxr - minr + 1);

int ***accum;  

accum = new int**[numer_filas];
for(int x = 0; x < numer_filas; ++x) {
    accum[x] = new int*[numero_columnas];
    for(int y = 0; y < numero_columnas; ++y) {
        accum[x][y] = new int[dimZ];
        for(int z = 0; z < dimZ; ++z) { 
      accum[x][y][z] = 0;
        }
    }
}

		int maximo=0;
		int r=0;
		int ejex=0;
		int ejey=0;



	for (int x = recortex; x < numero_columnas - recortex ; ++x)
	{
		for (int y = recortey; y < numer_filas - recortey; ++y)
		{
			for (int rad = minr; rad < maxr; ++rad)
			{
				if (*(*(matimg+y)+x)==1){
				for (int theta = 1; theta <= 360; theta+=2)//opcional realizar saltos de 2 en dos o dejar ++theta
				{
					int xdash=round(rad * std::cos(theta * PI / 180));
					int ydash=round(rad * std::sin(theta * PI / 180));

					if (((x+xdash)<numero_columnas)&&((x+xdash)>0)&&((y+ydash)<numer_filas)&&((y+ydash)>0)){
						int indice1 = (y+ydash);
						int indice2 = (x+xdash);
						int indice3 = (rad-minr+1);
	
			           accum[indice1][indice2][indice3] = accum[indice1][indice2][indice3] + 1;

                      		if (maximo < accum[indice1][indice2][indice3]){
							    r=indice3+minr;
								ejex=indice1;
								ejey=indice2;
								maximo=accum[indice1][indice2][indice3];
							}
                      }
				}
			}
			}
		}
	}
//////imrpimr imrprime x,y,r,maximo
std::cout<<"<<imprecion del archivo cicle_hough.h>>  "<<ejey+1<<" , "<<ejex+1<<" "<<r-1<<" maximo "<<maximo<<std::endl;

}
