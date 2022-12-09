#include <Textures.hpp>

gl::ResourceManager resourceManager;

void InitializeTextures() {
    resourceManager.loadTexture("sprites/test_sprite/sprite_square.jpg", false, "default_texture");
}