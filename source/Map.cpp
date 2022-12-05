#include <Map.hpp>

gl::Texture_base* defaultWallTexture = new gl::Texture("sprites/test_sprite/sprite_square.jpg", false);

Wall::Wall(Point<float> p1, Point<float> p2) :
    p1_(p1),
    p2_(p2),
    texture_(defaultWallTexture)
{}

Wall::Wall(Point<float> p1, Point<float> p2, gl::Texture_base* texture) :
    p1_(p1),
    p2_(p2),
    texture_(texture)
{}

Map::Map(std::vector<Wall> wallList) :
    wallList_(wallList)
{}

Map::AddWall(Wall wall) {
    wallList_.push_back(wall);
}