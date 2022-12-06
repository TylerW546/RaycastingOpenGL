#include <vector>
#include <glBase/gl.hpp>

#include "Util.hpp"
#include "Textures.hpp"

struct Wall {
    static gl::Texture_base* defaultWallTexture;

    Point<float> p1_;
    Point<float> p2_;
    gl::Texture_base* texture_;

    static void DefineDefaultWallTexture();

    Wall(Point<float> p1, Point<float> p2);
    Wall(Point<float> p1, Point<float> p2, gl::Texture_base* texture);
};

class Map {
    std::vector<Wall> wallList_;
    
    public:
    Map(std::vector<Wall> wallList);

    void AddWall(Wall wall);
};
