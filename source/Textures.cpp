#include <Textures.hpp>

gl::ResourceManager resourceManager;

void initializeTextures() {
    resourceManager.loadTexture("sprites/test_sprite/sprite_square.jpg", true, "default_texture");
}