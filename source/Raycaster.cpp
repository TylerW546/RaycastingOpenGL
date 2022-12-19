#include <Raycaster.hpp>

Ray::Ray(Point<float> position, float width, float angleOffset) {
    angleOffset_ = angleOffset;
    moveTo(position.x, position.y);
    setSize(1,1);
    setActiveTexture(resourceManager.texture("default_texture"));
}

float Ray::wallIntersectDist(Point<float> rayVect,
        Point<float> position, Wall wall, float viewMax, float viewMin) {
    
    wall.p1 -= position;
    wall.p2 -= position;

    // Basic check of quadrants
    if (rayVect.y > 0 != (wall.p1.y > 0 || wall.p2.y > 0))
        return 0;

    if (rayVect.x > 0 != (wall.p1.x > 0 || wall.p2.x > 0))
        return 0;
    
    // Check if they do intersect
    if (std::abs(rayVect.x) > std::abs(rayVect.y)) {
        int raycot = rayVect.x / rayVect.y;
        if ((raycot*wall.p1.y > 0) == (raycot*wall.p2.y > 0))
            return 0;
    } else {
        int raytan = rayVect.y / rayVect.x;
        if ((raytan*wall.p1.x > 0) == (raytan*wall.p2.x > 0))
            return 0;
    }

    std::cout << "PASSED INITIAL CHECKS -----------------\n"; 

    Point<float> deltaWall = wall.p2-wall.p1;
    float cross = rayVect.cross(deltaWall);
    // distance to interesction from ray origin
    float t = wall.p1.cross(deltaWall/cross);
    std::cout << "T value: " << t << "\n";
    if (t < viewMin || t > viewMax) return 0;
    return t;
}

float Ray::wallTextureIntersect(Point<float> rayVect, Wall wall) {
    Point<float> deltaWall = wall.p2-wall.p1;
    return wall.p1.cross(rayVect/rayVect.cross(deltaWall));
}

void Ray::updatePosition(Point<float> position, float width,
                        float angleOffset) {
    moveTo(position.x, position.y/2);
    setSize(1,1);
    angleOffset_ = angleOffset;
    width_ = width;
}

void Ray::update(Map& map, Point<float> position,
                float angle, float viewMax, float viewMin, float vertProportion) {
    
    struct {
        Wall* wall;
        float dist;
    } closest = {};

    angle += angleOffset_;

    int angleRad = Util::rad(angle);
    Point<float> rayVect{std::cos(angleRad), std::sin(angleRad)};
    
    float intersection = 0;
    for (auto wall : map) {
        intersection = wallIntersectDist(rayVect, position, *wall, viewMax, viewMin);
        if (closest.dist) std::cout << "WALL HIT --------------------------------------------------------\n";
        if (intersection < closest.dist) {
            closest.wall = wall;
            closest.dist = intersection;
        }
    }

    if (!closest.dist) {
        setScale(1,10);
    } else {
        setActiveTexture(closest.wall->texture);
        float texturePos = wallTextureIntersect(rayVect, *closest.wall);
        getRenderer()->setTextureRange(0,1, texturePos, texturePos);
        setSize(1,1);
        setScale(1, vertProportion/closest.dist);
    }

    // std::cout << getScaleY() << " : " << getPosX() << " " <<  getPosY() << "\n";
    std::cout << closest.dist << "\n";
}


RayCaster::RayCaster(gl::Game &game, float fovX, float fovY,
                    float pixelsPerRay, float viewMin, float viewMax) :
    fovX_(fovX), fovY_(fovY), pixelsPerRay_(pixelsPerRay),
    viewMin_(viewMin), viewMax_(viewMax)
{
    verticalProportion_ = WALL_HEIGHT / (2*std::tan(fovY_/2));
    screenSize_[0] = game.data().width;
    screenSize_[1] = game.data().height;
    float angleInc = fovX_ / (game.data().width/pixelsPerRay_);
    float angle = -fovX_;
    float xPos = pixelsPerRay_/2;
    while (rays_.size() < game.data().width/pixelsPerRay_) {
        Ray ray = {Point<float>{xPos, (float)game.data().height/2}, pixelsPerRay_, angle};
        ray.loadRenderer(&game);
        ray.setSize(1,1);
        rays_.push_back(ray);
        angle += angleInc, xPos += pixelsPerRay_;
    }
    usedRays_ = rays_.size();
}


void RayCaster::size_callback(uint16_t width, uint16_t height) {

    if (screenSize_[0] == width && screenSize_[1] == height) return;
    screenSize_[1] = height;
    screenSize_[0] = width;
    usedRays_ = width/pixelsPerRay_;


    float angleInc = fovX_ / usedRays_;
    float angle = -fovX_;
    float xPos = pixelsPerRay_/2;
    for (auto ray : rays_) {
        ray.updatePosition(Point<float>{xPos, (float)height/2}, pixelsPerRay_, angle);
        angle += angleInc, xPos += pixelsPerRay_;
    }

    while(rays_.size() < usedRays_) {
        rays_.push_back(Ray{Point<float>{xPos, (float)height/2}, pixelsPerRay_, angle});
        angle += angleInc, xPos += pixelsPerRay_;
    }
    
}

void RayCaster::render(const glm::mat4& windowProjection,
                        Map &map, Point<float> position, float direction) {
    std::cout << "updating entities " << rays_.size() << "\n";
    auto ray = rays_.begin();
    for (int i = 0; i < usedRays_; i++, ray++) {
        // std::cout << "Updating ray\n";
        (*ray).update(map, position, direction,
            viewMax_, viewMin_, verticalProportion_*screenSize_[1]);
        if (ray == rays_.end()) throw;
    }

    std::cout << "rendering entities\n";
    ray = rays_.begin();
    for (int i = 0; i < usedRays_; i++, ray++) {
        (*ray).render(windowProjection);
        
    }
}