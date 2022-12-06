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
};