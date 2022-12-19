#define _USE_MATH_DEFINES
#include <glBase/gl.hpp>

#include <iostream>

#include <cmath>
#include <math.h>
#include <vector>

#include "Textures.hpp"
#include "Character.hpp"
#include "Raycaster.hpp"
#include "Map.hpp"

class TestGame : public gl::Entity {
    RayCaster* raycaster_;
    Map map_;

    Point<float> position_;
    float direction_;

    public:

    TestGame(gl::Game &game) {
        std::vector<Wall*> wallList;
    
        std::cout << "hi" << "\n";
        Point<float> p1{100,100};
        Point<float> p2{150,-200};
        Point<float> p3{-200,-150};
        Point<float> p4{-150,250};
        
        wallList.push_back(new Wall(p1, p2));
        wallList.push_back(new Wall(p2, p3));
        wallList.push_back(new Wall(p3, p4));
        wallList.push_back(new Wall(p4, p1));

        map_ = Map(wallList);
        std::cout << "Initializing raycaster\n";
        raycaster_ = new RayCaster(game);

        position_ = {0, 0};
        direction_ = 0;
    }

    void GameSize_callback(uint16_t width, uint16_t height) override {
        raycaster_->size_callback(width, height);
    }

    void update(const gl::GameData &game) override {}

    virtual void render(const glm::mat4& windowProjection) override {
        std::cout << "about to render raycaster\n";
        raycaster_->render(windowProjection, map_, position_, direction_);
    }

};

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::dynamic_window);
    InitializeTextures();

    
    // game.loadEntity(new Character(Point<float>(10,10), 1.0, 1.0, 1.0, 1.0, 1.0));
    game.loadEntity(new TestGame(game));
    game.execute();

    return 0;
}