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
        return {-1, -1};

    if (rayVect.x > 0 != (wall.p1.x > 0 || wall.p2.x > 0))
        return {-1, -1};
    
    // Check if they do intersect
    if (std::abs(rayVect.x) > std::abs(rayVect.y) {
        int raycot = rayVect.x / rayVect.y;
        if ((raycot*wall.p1.y > 0) == (raycot*wall.p2.y > 0))
            return {-1, -1};
    } else {
        int raytan = rayVect.y / rayVect.x;
        if ((raycot*wall.p1.x > 0) == (raycot*wall.p2.x > 0))
            return {-1, -1};
    }

    point<float> deltaWall = wall.p2-wall.p1;
    float cross = rayVect.cross()
    // distance to interesction from ray origin
    float t = wall.p1.cross(deltaWall/cross);
    // placement of intersection on wall
    float u = wall.p1.cross(rayVect/cross);

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

