// #include <shader.hpp>


#define _USE_MATH_DEFINES
#include <glBase/gl.hpp>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <cmath>
#include <math.h>

class SimpleSprite : public gl::Sprite {
    float a[2] = {0,0};
    float v[2] = {0,0};
    float aRot = 0;
    float vRot = 0;

    static constexpr char *spriteFile = 
            "sprites/test_sprite/sprite_square.png";

    public:
    
    SimpleSprite(const gl::GameData &game) {
        moveTo(game.width/2, game.height/2);
    }

    static void initializeTextures(gl::GameData &data) {
        data.resourceManager.loadTexture
                (new gl::Texture(spriteFile, false), "simple_sprite");
    }

    void loadTextures(const gl::GameData &data) override {
        std::cout << "Activating Texture: " << data.resourceManager.texture("simple_sprite") << "\n";
        setActiveTexture(data.resourceManager.texture("simple_sprite"));
    }

    void GameSize_callback(uint16_t width, uint16_t height) override {
        moveTo(width/2, height/2);
    } 

    void update(const gl::GameData &game) override {
        // if (game.Keys[GLFW_KEY_LEFT]) {
        //     a[0] += 1*cos((getRotation()+180)*3.1415926/180);
        //     a[1] += 1*sin((getRotation()+180)*3.1415926/180);
        // }
        // if (game.Keys[GLFW_KEY_RIGHT]) {
        //     a[0] += 1*cos((getRotation())*3.1415926/180);
        //     a[1] += 1*sin((getRotation())*3.1415926/180);
        // }
        if (game.Keys[GLFW_KEY_UP]) {
            a[0] += 1*cos((getRotation()+270)*3.1415926/180);
            a[1] += 1*sin((getRotation()+270)*3.1415926/180);
        }
        // if (game.Keys[GLFW_KEY_DOWN]) {
        //     a[0] += 1*cos((getRotation()+90)*3.1415926/180);
        //     a[1] += 1*sin((getRotation()+90)*3.1415926/180);
        // }

        if (game.Keys[GLFW_KEY_A]) {
            aRot -= .4;
        }
        if (game.Keys[GLFW_KEY_D]) {
            aRot += .4;
        }

        v[0] += a[0];
        v[1] += a[1];
        vRot += aRot;
        a[0] = 0;
        a[1] = 0;
        aRot = 0;

        move(v[0], v[1]);
        rotate(vRot);

        v[0] *= .92;
        v[1] *= .92;
        vRot *= .92;

        if (getPosX() < 0) {
            setX(0);
        }
        if (getPosX() > game.width) {
            setX(game.width);
        }
        if (getPosY() <= 0) {
            setY(0);
        }
        if (getPosY() > game.height) {
            setY(game.height);
        }

        //rotate(1);
    }

};

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::stretch_window);
    
    SimpleSprite::initializeTextures(game.data());
    
    game.loadEntity(new SimpleSprite(game.data()));
    game.execute();

    return 0;
}