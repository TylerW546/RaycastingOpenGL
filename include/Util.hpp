#include <utility>
#include <math>
#include <math.h>

#define PI 3.14159265

float deg(float rad) {return rad*180/PI;}
float rad(float deg) {return deg*PI/180;}

template<typename T>
struct Point {
    T x;
    T y;
};


