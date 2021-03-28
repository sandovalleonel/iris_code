clear, clc, close all;
data=csvread("img.csv");

imshow(data)
##hold on
##plot( 299 , 243 ,"+");
##plot( 299 , 243+47 ,"+");
##plot(305 , 254 ,"+");
##plot(305 , 254+88,"+");

##im=imread("iris.jpg");
##im=im(:,1);
##
##fft(im)