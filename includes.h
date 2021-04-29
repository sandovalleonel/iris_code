#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <dirent.h>
#define  PI 3.14159265358979
#include "functions/double_functions.h"
#include "functions/int_functions.h"
#include "segmentacion/canny.h"
#include "segmentacion/adjgamma.h"
#include "segmentacion/nonmaxsup.h"
#include "segmentacion/hysthresh.h"
#include "segmentacion/circle_hough.h"
#include "normalizacion/normaliseiris.h"
#include "feature_extract/gaborconvolve.h"
//#include "match/svm-train.h"
//#include "match/svm.h"
//#include "match/svm.cpp"
//#include "match/svm-predict.h"