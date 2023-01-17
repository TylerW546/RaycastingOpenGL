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
        Environment e(20, 20);
        e.GenerateVertices();
        std::cout << "Verts generated\n";
        e.GenerateNodes();
        std::cout << "Nodes generated\n";
        e.MarchAllSquares();
        std::cout << "Marched all Squares\n";
        
        std::vector<Point<float>*> points;
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
        //wallList.push_back(new Wall(points[0], points[1]));

        std::cout<<"uEL size: "<<e.uniqueExteriorLines.size()<<"\n";
        std::cout<<"vert size: "<<e.vertices.size()<<"\n";
        for (int i = 0; i < 20; i+=2) {
            points.push_back(new Point<float> {1000*e.vertices.at(e.uniqueExteriorLines.at(i)*2), 1000*e.vertices.at(e.uniqueExteriorLines.at(i)*2+1)});
            std::cout<<1000*e.vertices.at(e.uniqueExteriorLines.at(i)*2)<<"   "<< 1000*e.vertices.at(e.uniqueExteriorLines.at(i)*2+1)<<"\n";
        }
        
        constexpr int wallCount = 5;
        for (int x = 0; x<wallCount; x+=2) {
            wallList.push_back(new Wall(*(points.at(x)), *(points.at(x+1))));
        }


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