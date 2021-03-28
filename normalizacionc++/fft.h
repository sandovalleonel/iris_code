
#include <iostream>
#include <cmath>
#include <cstddef>
#include <vector>
using std::size_t;
//using std::vector;
using std::cos;
using std::sin;
void computeDft( std::vector<double> &inreal,  std::vector<double> &inimag) {
    
    size_t n = inreal.size();
    for (size_t k = 0; k < n; k++) {  // For each output element
        double sumreal = 0;
        double sumimag = 0;
        for (size_t t = 0; t < n; t++) {  // For each input element
            double angle = 2 * M_PI * t * k / n;
            sumreal +=  inreal[t] * cos(angle) + inimag[t] * sin(angle);
            sumimag += -inreal[t] * sin(angle) + inimag[t] * cos(angle);
        }
        //outreal[k] = sumreal;
        printf("%lf   ***  ",sumreal );
        printf("%lf\n",sumimag ); //outimag[k] = sumimag;
    }


}


/*
std::vector<double> input;
std::vector<double> in_img;
std::vector<double> result1;
std::vector<double> result2;
//vector<complex<double>> output;
int main(int argc, char const *argv[])
{
    input.push_back(55);
    input.push_back(15);
    input.push_back(86);
   input.push_back(24);
    input.push_back(66);
    input.push_back(245);
    input.push_back(76);

    in_img.push_back(0);
    in_img.push_back(0);
    in_img.push_back(0);    
    in_img.push_back(0);
    in_img.push_back(0);
    in_img.push_back(0);
    in_img.push_back(0);

    computeDft(input,in_img);
    return 0;
}*/