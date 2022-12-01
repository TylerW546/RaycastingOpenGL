#include "Util.hpp"

#include <glBase/gl.hpp>

class Ray : public gl::Sprite {
    Ray(const gl::GameData &game)
};

class RayCaster {
    gl::EntityList_;
    int screenWidth_;


    RayCaster(const gl::GameData &game);
    ~RayCaster() {}

    void size_callback(const gl::GameData &game) {screenWidth_ = game.width;}

    void render(Map* map, Point<float> position, float direction);

};