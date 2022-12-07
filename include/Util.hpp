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
};