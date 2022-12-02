#include <vector>
#include <glBase/gl.hpp>

#include "Util.hpp"

struct Wall {
    Point<float> p1_;
    Point<float> p2_;
    gl::Texture_base* texture_;

    Wall(Point<float> p1, Point<float> p2);
    Wall(Point<float> p1, Point<float> p2, gl::Texture_base* texture);
};

class Map {
    std::vector<Wall> wallList_;
    
    public:
    Map(std::vector<Wall> wallList);

    AddWall(Wall wall);
};
