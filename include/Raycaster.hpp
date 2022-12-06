#include "Util.hpp"

#include <glBase/gl.hpp>

class Ray : public gl::Sprite {
    float textureRange_[2];
    float angleOffset_;
    
    Ray(const gl::GameData &game, float position, float width);

    void updatePosition(const gl::GameData &game, float position, float width);

    void update(Map* map, point<float> position, float angle);


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