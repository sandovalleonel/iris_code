clc;clear;close all;


im1=csvread("test.csv");
imshow(im1)
%interno 126 , 96 16
%externo 122,97 ,37
%359 , 268 22
x=182;
y=100;
r=13;
hold on
plot(x,y,'*')
plot(x+r,y,'*')
plot(x-r,y,'*')
plot(x,y+r,'*')
plot(x,y-r,'*')
return
%%%%%%%%%%%%x=columnas
%240 100%
%126  x
%%x=52.5%

%640 100%
%x   52.5%
%x=640*0.525
%x=336----------

%%%%%%%y=filas
%178 100%
%96   y
%y=53.9325%
%480 100%
%y   53.9325%
%y=480*0.539325
%y=259
%%%%%%%r
%saber cuanto% le bajaro a la img
%640  100%
%240   x
%x=37.5%

%480  100%
%178   x
%x=37.0833
%-----
%16   37.5%
%x     100%
%x=42.6666=43

figure
im2=imread("img/iris.jpg");
imshow(im2)
hold on
x2=336;
y2=259;
r2=43;
plot(x2,y2,'*');
plot(x2,y2+r2,'*');
plot(x2,y2+r2,'*');