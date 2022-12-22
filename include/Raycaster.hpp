#pragma once

#include "Util.hpp"
#include "Map.hpp"

#include <glBase/gl.hpp>
#include <list>

class Ray : public gl::Sprite {

    float textureRange_[2];
    float angleOffset_;
    float width_;

    float angleCos_;

    // Get distance fo the wall from position along the ray
    // Returns 0 if wall isn't intersected by ray
    static float wallIntersectDist(Point<float> rayVect,
        Point<float> position, Wall wall, float viewMax, float viewMin);
    
    // Position on texture intersected by ray
    static float wallTextureIntersect(Point<float> rayVect, Wall wall);

    public:

    Ray(Point<float> position, float width, float angleOffset);

    void updatePosition(Point<float> position, float width, float angleOffset);

    void update(Map& map, Point<float> position, float angle,
        float viewMax, float viewMin, float vertProportion);


};

class RayCaster {

    static constexpr float PIXELS_PER_RAY_d = 1;
    static constexpr float FOV_X_d = 60;
    static constexpr float FOV_Y_d = 50;
    static constexpr float VIEW_MIN_d = 10;
    static constexpr float VIEW_MAX_d = 1000;

    static constexpr float WALL_HEIGHT = 20;

    float pixelsPerRay_;
    float fovX_;
    float fovY_;
    float verticalProportion_; // Buffered value relating distance of a wall to height on screen

    float viewMin_;
    float viewMax_;
    
    float screenSize_[2];

    int usedRays_;
    std::list<Ray> rays_;

    public:

    RayCaster(gl::Game &game, float fovX = FOV_X_d, 
                float fovY = FOV_Y_d, float pixelsPerRay = PIXELS_PER_RAY_d,
                float viewMin = VIEW_MIN_d, float viewMax = VIEW_MAX_d);
    ~RayCaster() {}


    void size_callback(uint16_t width, uint16_t height);

    void render(const glm::mat4& windowProjection,
                Map &map, Point<float> position, float direction);
};