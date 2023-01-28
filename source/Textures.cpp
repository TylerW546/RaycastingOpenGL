#include <Textures.hpp>

gl::ResourceManager resourceManager;

void initializeTextures() {
    resourceManager.loadTexture("sprites/test_sprite/sprite_square.jpg", true, "default_texture");
    for (int i =0; i<16; i++) {
        std::string loc = "sprites/test_sprite/";
        loc.append(std::to_string(i));
        loc.append(".jpg");
        resourceManager.loadTexture(loc.data(), false, std::to_string(i));
    }
}