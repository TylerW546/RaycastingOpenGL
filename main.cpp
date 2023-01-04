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
#include "Environment.hpp"

class TestGame : public gl::Entity {
    RayCaster* raycaster_;
    Map map_;

    Point<float> position_;
    float direction_;
    float speed;
    float rotSpeed;

    public:

    TestGame(gl::Game &game) {
        Environment e(150, 150);
        e.GenerateVertices();
        e.GenerateNodes();
        e.SetUpCombs();
        e.MarchAllSquares();
        
        std::vector<Wall*> wallList;
    
        //std::cout << "hi" << "\n";
        // std::vector<Point<float>> points = {
        //     Point<float> {200,200},
        //     Point<float> {200,-200},
        //     Point<float> {-200,-200},
        //     Point<float> {-200,200},

        //     Point<float> {-50,200},
        //     Point<float> {-50,550},
        //     Point<float> {300,550},

        //     Point<float> {300,700},
        //     Point<float> {700,700},
        //     Point<float> {700,300},
        //     Point<float> {300,300},

        //     Point<float> {300,450},
        //     Point<float> {50,450},
        //     Point<float> {50,200}
        // };

        std::vector<Point<float>> points;
    
        for (int i = 1; i < 100; i++) {
            points.push_back(Point<float> {100*e.vertices[e.allLines[i]*3],100*e.vertices[e.allLines[i]*3+1]});
        }
        
        constexpr int wallCount = 14;
        for (int x = 0; x<wallCount; x++) {
            wallList.push_back(new Wall(points[x], points[(x+1)%wallCount]));
        }

        // wallList.push_back(new Wall(points[0], points[1]));

        map_ = Map(wallList);
        //std::cout << "Initializing raycaster\n";
        raycaster_ = new RayCaster(game);

        position_ = {0, 0};
        direction_ = 0;
        speed = 5;
        rotSpeed = 2;

    }

    void GameSize_callback(uint16_t width, uint16_t height) override {
        raycaster_->size_callback(width, height);
    }

    void update(const gl::GameData &game) override {
        //direction_ = std::fmod((direction_ + 1),360);

        if (game.Keys[GLFW_KEY_A]) {
            position_.x += speed*cos(Util::rad(direction_+90));
            position_.y += speed*sin(Util::rad(direction_+90));
        }
        if (game.Keys[GLFW_KEY_D]) {
            position_.x += speed*cos(Util::rad(direction_-90));
            position_.y += speed*sin(Util::rad(direction_-90));
        }
        if (game.Keys[GLFW_KEY_W]) {
            position_.x += speed*cos(Util::rad(direction_));
            position_.y += speed*sin(Util::rad(direction_));
        }
        if (game.Keys[GLFW_KEY_S]) {
            position_.x += speed*cos(Util::rad(direction_+180));
            position_.y += speed*sin(Util::rad(direction_+180));
        }

        if (game.Keys[GLFW_KEY_LEFT]) {
            direction_ += rotSpeed;
        }
        if (game.Keys[GLFW_KEY_RIGHT]) {
            direction_ -= rotSpeed;
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