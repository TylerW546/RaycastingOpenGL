#define _USE_MATH_DEFINES
#include <glBase/gl.hpp>

#include <iostream>

#include <cmath>
#include <math.h>
#include <vector>
#include <Map.hpp>

#include "Textures.hpp"

int main() {
    gl::Game game(24, 800, 900, "gl Library Test", gl::WindowType::stretch_window);
    InitializeTextures();

    std::vector<Wall> wallList;
    
    std::cout << "hi" << "\n";
    Point<float> p1{10,10};
    Point<float> p2{-10,20};
    
    wallList.push_back(Wall(p1, p2));

    Map defaultMap = Map(wallList);
    
    game.execute();

    return 0;
}