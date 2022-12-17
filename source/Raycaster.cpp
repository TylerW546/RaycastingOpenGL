#include <Raycaster.hpp>

Ray::Ray(const gl::GameData &game, float position, float width) {
    moveTo(position, game.height/2);
    setSize(1,1);
}

std::pair<float, float>
Ray::wallIntersect(float angle, Point<float> rayVect,
        Point<float> position, Wall wall, float viewMax, float viewMin) {
    
    wall.p1 -= position;
    wall.p2 -= position;

    // Basic check of quadrants
    if (rayVect.y > 0 != (wall.p1.y > 0 || wall.p2.y > 0))
        return {0,0};

    if (rayVect.x > 0 != (wall.p1.x > 0 || wall.p2.x > 0))
        return {0,0};
    
    // Check if they do intersect
    if (std::abs(rayVect.x) > std::abs(rayVect.y)) {
        int raycot = rayVect.x / rayVect.y;
        if ((raycot*wall.p1.y > 0) == (raycot*wall.p2.y > 0))
            return {0,0};
    } else {
        int raytan = rayVect.y / rayVect.x;
        if ((raytan*wall.p1.x > 0) == (raytan*wall.p2.x > 0))
            return {0,0};
    }

    Point<float> deltaWall = wall.p2-wall.p1;
    float cross = rayVect.cross()
    // distance to interesction from ray origin
    float t = wall.p1.cross(deltaWall/cross);
    if (t < viewMin || t > viewMax) return {0,0};
    // placement of intersection on wall
    float u = wall.p1.cross(rayVect/cross);
    return {t, u};
}

void Ray::updatePosition(const gl::GameData &game, float position, float width,
                        float angleOffset) {
    moveTo(position, game.height/2);
    setSize(1,1);
    angleOffset_ = angleOffset;
    width_ = width;
}

void Ray::update(const gl::GameData &game, Map& map, Point<float> position,
                float angle, float viewMax, float viewMin) {
    struct {
        gl::Texture_base* texture;
        float dist; float textPosition;
    } closest = {};

    angle += angleOffset_;

    int angleRad = rad(angle);
    Point<float> rayVect{std::cos(angleRad), std::sin(angleRad)};
    
    // pair<dist, textPosition>
    std::pair<float, float> intersection;
    for (auto wall : map) {
        intersection = wallIntersect(angle, rayVect, position, wall,
                                        viewMax, viewMin);
        if (intersection.first && intersection.first < closest.dist) {
            closest.texture = wall.texture;
            closest.dist = intersection.first;
            closest.textPosition = intersection.second;
        }
    }

    if (!closest) {
        setScale(1,0);
    } else {
        setActiveTexture(closest.texture);
        getRenderer()->setTextureRange(0,1, closest.textPosition, closest.textPosition);
        setSize(1,1);
        setScale(1,(game.height - PROPORTION/closest.dist/2));
    }
}


RayCaster::RayCaster(const gl::GameData &game, float fovX, float fovY
        float pixelsPerRay = PIXELS_PER_RAY_d) :
    fovX_(fovX), fovY_(fovY), pixelsPerRay_(pixelsPerRay)
        {
    
}