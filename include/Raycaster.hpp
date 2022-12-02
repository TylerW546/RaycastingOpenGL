#include "Util.hpp"

#include <glBase/gl.hpp>

class Ray : public gl::Sprite {
    gl::Texture_base* texture_;
    float textureRange_[2];
    float angleOffset_;
    
    Ray(float position, float width);

};

class RayCaster {

    static constexpr PIXELS_PER_RAY = 1;

    gl::EntityList_;
    int screenWidth_;
    gl::EntityList;

    RayCaster(const gl::GameData &game);
    ~RayCaster() {}

    void size_callback(const gl::GameData &game);

    void render(Map* map, Point<float> position, float direction);
};