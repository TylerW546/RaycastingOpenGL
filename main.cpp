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
    float speed;
    float rotSpeed;

    public:

    TestGame(gl::Game &game) {
        std::vector<Wall*> wallList;
    
        //std::cout << "hi" << "\n";
        std::vector<Point<float>> points = {
            Point<float> {200,200},
            Point<float> {200,-200},
            Point<float> {-200,-200},
            Point<float> {-200,200},

            Point<float> {-50,200},
            Point<float> {-50,550},
            Point<float> {300,550},

            Point<float> {300,700},
            Point<float> {700,700},
            Point<float> {700,300},
            Point<float> {300,300},

            Point<float> {300,450},
            Point<float> {50,450},
            Point<float> {50,200}
        };
        
        for (int x = 0; x<14; x++) {
            wallList.push_back(new Wall(points[x], points[(x+1)%14]));
        }

        map_ = Map(wallList);
        //std::cout << "Initializing raycaster\n";
        raycaster_ = new RayCaster(game);

        position_ = {0, 0};
        direction_ = 0;
        speed = 5;
        rotSpeed = 1;

    }

    void GameSize_callback(uint16_t width, uint16_t height) override {
        raycaster_->size_callback(width, height);
    }

    void update(const gl::GameData &game) override {
        //direction_ = std::fmod((direction_ + 1),360);

        if (game.Keys[GLFW_KEY_LEFT]) {
            position_.x += speed*cos((direction_+180)*3.1415926/180);
            position_.y += speed*sin((direction_+180)*3.1415926/180);
        }
        if (game.Keys[GLFW_KEY_RIGHT]) {
            position_.x += speed*cos((direction_)*3.1415926/180);
            position_.y += speed*sin((direction_)*3.1415926/180);
        }
        if (game.Keys[GLFW_KEY_UP]) {
            position_.x += speed*cos((direction_+270)*3.1415926/180);
            position_.y += speed*sin((direction_+270)*3.1415926/180);
        }
        if (game.Keys[GLFW_KEY_DOWN]) {
            position_.x += speed*cos((direction_+90)*3.1415926/180);
            position_.y += speed*sin((direction_+90)*3.1415926/180);
        }

        if (game.Keys[GLFW_KEY_A]) {
            direction_ -= rotSpeed;
        }
        if (game.Keys[GLFW_KEY_D]) {
            direction_ += rotSpeed;
        }

        //std::cout << direction_ << "\n   ";
    }

    virtual void render(const glm::mat4& windowProjection) override {
        //std::cout << "about to render raycaster\n";
        raycaster_->render(windowProjection, map_, position_, direction_);
    }

};

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::dynamic_window);
    initializeTextures();

    
    // game.loadEntity(new Character(Point<float>(10,10), 1.0, 1.0, 1.0, 1.0, 1.0));
    game.loadEntity(new TestGame(game));
    game.execute();

    return 0;
}