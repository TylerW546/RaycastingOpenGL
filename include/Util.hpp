#include <utility>
#include <math>
#include <math.h>

#define PI 3.14159265

template<typename T>
struct Point {
    T x;
    T y;
};


std::pair<float, float>
wallIntersect(float angle, Point<float> position, Wall wall) {
    float radians = angle*PI/180;
    int raysin = std::sin(angle);
    int raycos = std::cos(angle);
    
    raytan = raysin / raycos;

}