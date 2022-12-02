// #include <shader.hpp>


#define _USE_MATH_DEFINES
#include <glBase/gl.hpp>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <cmath>
#include <math.h>
#include <vector>
#include <Map.hpp>

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::stretch_window);

    std::vector<Wall> wallList;
    Point<float> coordinate1{10,10};
    Point<float> coordinate2{-10, 10};
    wallList.push_back(Wall(coordinate1, coordinate2));

    Map defaultMap = Map(wallList);
    
    game.execute();

    return 0;
}