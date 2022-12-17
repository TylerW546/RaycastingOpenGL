#pragma once

template<typename T>
struct Point;

#include <utility>
#include <math.h>
#include <cstdlib>

#define PI 3.14159265
#include <cstdlib>

float deg(float rad) {return rad*180/PI;}
float rad(float deg) {return deg*PI/180;}


template<typename T>
struct Point {
    T x;
    T y;

    Point<T> operator + (Point<T> const obj) {
        Point<T> out;
        out.x = x + obj.x;
        out.y = y + obj.y; 
        return out;
    }

    Point<T> operator += (Point<T> const obj) {
        x += obj.x;
        y += obj.y;
    }

    Point<T> operator - (Point<T> const obj) {
        Point<T> out;
        out.x = x - obj.x;
        out.y = y - obj.y; 
        return out;
    }

    Point<T> operator -= (Point<T> const obj) {
        x -= obj.x;
        y -= obj.y;
    }

    Point<T> operator * (T const scalar) {
        x *= scalar;
        y *= scalar;
    }

    Point<T> operator / (T const scalar) {
        x /= scalar;
        y /= scalar;
    }

    Point<T> operator % (T const scalar) {
        x %= scalar;
        y %= scalar;
    }

    T dotProduct(Point<T> const obj) {
        T out = x * obj.x + y * obj.y;
        return out;
    }

    T crossProduct(Point<T> const obj) {
        T out = x * obj.y - y * obj.x;
        return out;
    }

    T getMagnitude() {
        return sqrt(pow(x, 2), pow(y, 2));
    }

    T distanceTo(Point<T> const obj) {
        return sqrt(pow(x-obj.x, 2), pow(y-obj.y, 2));
    }

    void setMagnitude(T scalar) {
        T scale = scalar / getMagnitude;
        x *= scale;
        y *= scale; 
    }
};
