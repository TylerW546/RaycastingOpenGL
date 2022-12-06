#include <vector>
#include <glBase/gl.hpp>

#include "Util.hpp"

struct Wall {
    Point<float> p1;
    Point<float> p2;
    gl::Texture_base* texture;

    Wall(Point<float> p1, Point<float> p2);
    Wall(Point<float> p1, Point<float> p2, gl::Texture_base* texture);

    
};

class Map {
    std::vector<Wall> wallList_;
    
    public:
    Map(std::vector<Wall> wallList);

    void AddWall(Wall wall);

    void length() {return wallList_.size();}
    void wall(int n) {return wallList_[0];}
    void begin() {return wallList_.begin();}
};
