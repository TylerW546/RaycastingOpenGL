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
        Environment* e = new Environment(50, 50);
        e->GenerateVertices();
        std::cout << "Verts generated\n";
        e->GenerateNodes();
        std::cout << "Nodes generated\n";
        e->MarchAllSquares();
        std::cout << "Marched all Squares\n";
        
        std::vector<Point<float>*> points;
        std::vector<Wall*> wallList;
    
        // std::vector<Point<float>> pointsN = {
        //     Point<float> {300,950},
        //     Point<float> {250,900},
        //     Point<float> {400,950},
        //     Point<float> {300,950},
        //     Point<float> {400,950},
        //     Point<float> {450,900},
        //     Point<float> {200,850},
        //     Point<float> {150,800},
        //     Point<float> {250,900},
        //     Point<float> {200,850},
        //     Point<float> {450,900},
        //     Point<float> {500,850},
        //     Point<float> {500,850},
        //     Point<float> {550,800},
        //     Point<float> {150,800},
        //     Point<float> {150,700},
        //     Point<float> {550,800},
        //     Point<float> {550,700},
        //     Point<float> {-600,650},
        //     Point<float> {-650,600},
        //     Point<float> {-500,650},
        //     Point<float> {-600,650},
        //     Point<float> {-500,650},
        //     Point<float> {-450,600}
        // };

        // for (int x = 0; x < 9; x++) {
        //     wallList.push_back(new Wall(pointsN[x*2], pointsN[x*2+1]));
        // }

        // std::cout<<"uEL size: "<<e.uniqueExteriorLines.size()<<"\n";
        // std::cout<<"vert size: "<<e.vertices.size()<<"\n";
        // for (int i = 0; i < 10; i++) {
        //     points.push_back(new Point<float>{1000*e.vertices.at(e.mainMesh.at(i)*2), 1000*(e.vertices.at(e.mainMesh.at(i)*2+1))});
        // }
        // constexpr int wallCount = 2;
        // for (int x = 0; x<wallCount; x++) {
        //     wallList.push_back(new Wall(points.at(x*2), points.at(x*2+1)));
        // }

        for (int i = 0; i < e->uniqueExteriorLines.size(); i+=2) {
            Point<float>* p1 = new Point<float> {2500*e->vertices.at(e->uniqueExteriorLines.at(i)*2), 2500*(e->vertices.at(e->uniqueExteriorLines.at(i)*2+1))};
            Point<float>* p2 = new Point<float> {2500*e->vertices.at(e->uniqueExteriorLines.at(i+1)*2), 2500*(e->vertices.at(e->uniqueExteriorLines.at(i+1)*2+1))};
            //std::cout<<p1->x<<" "<<p1->y<<"   "<<p2->x<<" "<<p2->y<<"\n";
            wallList.push_back(new Wall(p1,p2));
        }
        // delete e;
        // std::cout<<"donewalls\n";

        map_ = Map(wallList);

        std::cout<<"map created\n";
        //std::cout << "Initializing raycaster\n";
        raycaster_ = new RayCaster(game);

        std::cout<<"raycaster\n";

        position_ = {0, 0};
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

        //std::cout << direction_ << "\n   ";

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