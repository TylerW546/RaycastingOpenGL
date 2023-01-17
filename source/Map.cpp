#include <Map.hpp> 

Wall::Wall(Point<float>* point1, Point<float>* point2) :
    p1(point1),
    p2(point2),
    texture(resourceManager.texture("default_texture"))
{}

Wall::Wall(Point<float>* point1, Point<float>* point2, gl::Texture_base* texture) :
    p1(point1),
    p2(point2),
    texture(texture)
{}

Map::Map(std::vector<Wall*> wallList) :
    wallList_(wallList)
{}

Map::~Map() {

}

void Map::AddWall(Wall* wall) {
    wallList_.push_back(wall);
}