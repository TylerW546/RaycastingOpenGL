#include <Raycaster.hpp>

Ray::Ray(const gl::GameData &game, float position, float width) {
    moveTo(position, game.height/2);
    setSize(1,1);
}

void Ray::updatePosition(const gl::GameData &game, float position, float width) {
    moveTo(position, game.height/2);
    setSize(1,1);
}

void Ray::update(Map& map, point<float> position, float angle) {
    struct {
        gl::Texture_base* texture_;
        float dist; float textPosition;
    } closest;
    for (auto wall = map.begin(); wall; wall++) {
        
    }
}