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

    Environment* e = new Environment(50, 50);
    int mapSize = 2500;

    public:

    TestGame(gl::Game &game) {
        e->GenerateVertices();
        std::cout << "Verts generated\n";
        e->GenerateNodes();
        std::cout << "Nodes generated\n";
        e->MarchAllSquares();
        std::cout << "Marched all Squares\n";
        
        std::vector<Point<float>*> points;
        std::vector<Wall*> wallList;


        for (int i = 0; i < e->uniqueExteriorLines.size(); i+=2) {
            Point<float>* p1 = new Point<float> {mapSize*e->vertices.at(e->uniqueExteriorLines.at(i)*2), mapSize*(e->vertices.at(e->uniqueExteriorLines.at(i)*2+1))};
            Point<float>* p2 = new Point<float> {mapSize*e->vertices.at(e->uniqueExteriorLines.at(i+1)*2), mapSize*(e->vertices.at(e->uniqueExteriorLines.at(i+1)*2+1))};
            //std::cout<<p1->x<<" "<<p1->y<<"   "<<p2->x<<" "<<p2->y<<"\n";
            wallList.push_back(new Wall(p1,p2));
        }

        map_ = Map(wallList);

        std::cout<<"map created\n";
        //std::cout << "Initializing raycaster\n";
        raycaster_ = new RayCaster(game);

        std::cout<<"raycaster\n";

        position_ = {-mapSize, -mapSize};
        direction_ = 0;
        speed = 5;
        rotSpeed = 2;
        std::cout<<"done\n";
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

        if (game.Keys[GLFW_KEY_P]) {
            e->nM.PrintMap((-position_.y/mapSize+1)/2*e->nM.NODES_HEIGHT, (position_.x/mapSize+1)/2*e->nM.NODES_WIDTH);
        }
    }

    virtual void render(const glm::mat4& windowProjection) override {
        raycaster_->render(windowProjection, map_, position_, direction_);
    }
};

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::dynamic_window);
    std::cout<<"Game created\n";
    initializeTextures();
    std::cout<<"txt\n";

    
    // game.loadEntity(new Character(Point<float>(10,10), 1.0, 1.0, 1.0, 1.0, 1.0));
    std::cout<<"loadingmain\n";
    TestGame* testG = new TestGame(game);
    std::cout<<"game made";
    game.loadEntity(testG);
    std::cout<<"loaded\n";
    game.execute();

    //delete testG;
    
    return 0;
}