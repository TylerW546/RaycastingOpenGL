#include <Raycaster.hpp>

Ray::Ray(const gl::GameData &game, float position, float width) {
    moveTo(position, game.height/2);
    setSize(1,1);
}

void Ray::updatePosition(const gl::GameData &game, float position, float width) {
    moveTo(position, game.height/2);
    setSize(1,1);
}

void Ray::update(Map &map, Point<float> position, float angle) {
    struct {
        gl::Texture_base* texture_;
        float dist; float textPosition;
    } closest;
    for (auto wall = map.begin(); wall != map.end(); wall++) {
        
    }
}

std::pair<float, float>
Ray::checkIntersect(float angle, Point<float> position, Wall &wall) {
    float radians = angle*PI/180;
    int raysin = std::sin(angle);
    int raycos = std::cos(angle);
    
    int raytan = raysin / raycos;

}