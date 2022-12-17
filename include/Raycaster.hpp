#include "Util.hpp"
#include "Map.hpp"

#include <glBase/gl.hpp>

class Ray : public gl::Sprite {
    float textureRange_[2];
    float angleOffset_;

    static std::pair<float, float>
        checkIntersect(float angle, Point<float> position, Wall &wall);
    
    Ray(const gl::GameData &game, float position, float width);

    void updatePosition(const gl::GameData &game, float position, float width);

    void update(Map &map, Point<float> position, float angle);


};

class RayCaster {

    static constexpr int PIXELS_PER_RAY = 1;

    gl::EntityList entityList_;
    int screenWidth_;

    RayCaster(const gl::GameData &game);
    ~RayCaster() {}

    void size_callback(const gl::GameData &game);

    void render(Map* map, Point<float> position, float direction);
};