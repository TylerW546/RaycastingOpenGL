#define _USE_MATH_DEFINES
#include <glBase/gl.hpp>

#include <iostream>
#include <string>
#include <sstream>

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
    Point<float> posCheck_;
    float direction_;
    float speed;
    float rotSpeed;

    Environment* e = new Environment(50, 50);
    int mapSize = 2500;

    public:

    TestGame(gl::Game &game) {
        e->GenerateNodes();
        e->MarchAllSquares();

        std::vector<Point<float>*> points;
        std::vector<Wall*> wallList;

        for (int i = 0; i < e->uniqueExteriorLines.size(); i+=2) {
            Point<float>* p1 = new Point<float> {mapSize*( ( (float) ( e->uniqueExteriorLines.at(i) % (e->VERTS_WIDTH)) / (e->VERTS_WIDTH-1)) * 2 - 1) , 
                                                 -mapSize*( ( (float) ( e->uniqueExteriorLines.at(i)) / (e->VERTS_HEIGHT) / (e->VERTS_HEIGHT-1)) * 2 - 1)};
            Point<float>* p2 = new Point<float>  {mapSize*( ( (float) ( e->uniqueExteriorLines.at(i+1) % (e->VERTS_WIDTH)) / (e->VERTS_WIDTH-1)) * 2 - 1) , 
                                                 -mapSize*( ( (float) ( e->uniqueExteriorLines.at(i+1)) / (e->VERTS_HEIGHT) / (e->VERTS_HEIGHT-1)) * 2 - 1)};
            int code = e->wallCodes.at(i);
            //std::cout<<p1->x<<" "<<p1->y<<"   "<<p2->x<<" "<<p2->y<<"\n";
            wallList.push_back(new Wall(p1,p2,resourceManager.texture(std::to_string(code))));
        }

        map_ = Map(wallList);

        std::cout<<"map created\n";
        //std::cout << "Initializing raycaster\n";
        raycaster_ = new RayCaster(game);

        std::cout<<"raycaster\n";

        bool found = false;
        for (float i = 0; i < e->SQUARES_HEIGHT && !found; i++)
        {
            for (float j = 0; j < e->SQUARES_WIDTH && !found; j++)
            {
                if (e->GetCode((int)i,(int)j) == 0) {
                    position_ = {(j/e->SQUARES_WIDTH*2-1)*mapSize, -(i/e->SQUARES_HEIGHT*2-1)*mapSize};
                    found = true;
                }
            }
        }

        direction_ = 0;
        speed = 10;
        rotSpeed = 3;
    }

    void GameSize_callback(uint16_t width, uint16_t height) override {
        raycaster_->size_callback(width, height);
    }

    void update(const gl::GameData &game) override {
        //direction_ = std::fmod((direction_ + 1),360);

        posCheck_ = {position_.x, position_.y};
        if (game.Keys[GLFW_KEY_A]) {
            posCheck_.x += speed*cos(Util::rad(direction_+90));
            posCheck_.y += speed*sin(Util::rad(direction_+90));
        }
        if (game.Keys[GLFW_KEY_D]) {
            posCheck_.x += speed*cos(Util::rad(direction_-90));
            posCheck_.y += speed*sin(Util::rad(direction_-90));
        }
        if (game.Keys[GLFW_KEY_W]) {
            posCheck_.x += speed*cos(Util::rad(direction_));
            posCheck_.y += speed*sin(Util::rad(direction_));
        }
        if (game.Keys[GLFW_KEY_S]) {
            posCheck_.x += speed*cos(Util::rad(direction_+180));
            posCheck_.y += speed*sin(Util::rad(direction_+180));
        }
        //if (e->GetCode(-posCheck_.y/mapSize+1)/2*e->SQUARES_HEIGHT, (posCheck_.x/mapSize+1)/2*e->SQUARES_WIDTH) != 15) {
        std::vector<float> posIndexes = e->IndexAtPos(position_.x, position_.y, mapSize);
        std::vector<float> posCheckIndexes = e->IndexAtPos(posCheck_.x, posCheck_.y, mapSize);
        if (e->PositionInAir(posCheckIndexes[0], posCheckIndexes[1])) {
            position_.x = posCheck_.x;
            position_.y = posCheck_.y;
        } else {
            std::vector<float> finalIndexes = e->WallIntersection(posIndexes[0], posIndexes[1], posCheckIndexes[0], posCheckIndexes[1]);
        }

        if (game.Keys[GLFW_KEY_LEFT]) {
            direction_ += rotSpeed;
        }
        if (game.Keys[GLFW_KEY_RIGHT]) {
            direction_ -= rotSpeed;
        }

        if (game.Keys[GLFW_KEY_P]) {
            e->nM.PrintMap((-position_.y/mapSize+1)/2*e->nM.NODES_HEIGHT, (position_.x/mapSize+1)/2*e->nM.NODES_WIDTH);
            std::cout<<e->GetCode((-posCheck_.y/mapSize+1)/2*e->SQUARES_HEIGHT, (posCheck_.x/mapSize+1)/2*e->SQUARES_WIDTH)<<"\n";
        }
    }

    virtual void render(const glm::mat4& windowProjection) override {
        raycaster_->render(windowProjection, map_, position_, direction_);
    }
};

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::dynamic_window);
    initializeTextures();

    
    // game.loadEntity(new Character(Point<float>(10,10), 1.0, 1.0, 1.0, 1.0, 1.0));
    TestGame* testG = new TestGame(game);
    game.loadEntity(testG);
    game.execute();

    //delete testG;
    
    return 0;
}