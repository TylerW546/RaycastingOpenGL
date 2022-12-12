#include "Util.hpp"

#include <glBase/gl.hpp>
#include <list>

class Ray : public gl::Sprite {

    float textureRange_[2];
    float angleOffset_;
    float width_;

    
    Ray(const gl::GameData &game, float position, float width);

    static std::pair<float, float>
        Ray::wallIntersect(float angle, Point<float> position, Wall wall);
    static float heightFromDist(float distance);

    void updatePosition(const gl::GameData &game, float position, float width);

    
    void update(Map* map, point<float> position, float angle);


};

class RayCaster {

    static constexpr float PIXELS_PER_RAY_d = 1;
    static constexpr float FOV_X_d = 60;
    static constexpr float FOV_Y_d = 50;

    float pixelsPerRay_;
    float fovX_;
    float fovY_;
    float fovYcos_; // Buffered value for the sin of the fov

    std::List<Ray> rays_;
    int screenWidth_;

    RayCaster(const gl::GameData &game, float fovX = FOV_X_d, 
                float fovY = FOV_Y_d, float pixelsPerRay = PIXELS_PER_RAY_d);
    ~RayCaster() {}

    void size_callback(const gl::GameData &game);

    void render(Map* map, Point<float> position, float direction);
};