#pragma once

#include <vector>
#include <glBase/gl.hpp>

struct Wall;

#include "Util.hpp"
#include "Textures.hpp"

struct Wall {
    Point<float> p1;
    Point<float> p2;
    gl::Texture_base* texture;

    static void DefineDefaultWallTexture();

    Wall(Point<float> p1, Point<float> p2);
    Wall(Point<float> p1, Point<float> p2, gl::Texture_base* texture);

    
};

class Map {
    std::vector<Wall*> wallList_;
    
    public:
    Map() {}
    Map(std::vector<Wall*> wallList);

    void AddWall(Wall* wall);

    size_t length() {return wallList_.size();}
    Wall* wall(int n) {return wallList_[n];}
    auto begin() {return wallList_.begin();}
    auto end() {return wallList_.end();}
};
