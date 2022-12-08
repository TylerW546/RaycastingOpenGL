#include "glBase/Entity.hpp"

class Interface : public std::Entity {
    Character* character;
    
    public: 
    virtual void render(const glm::mat4& windowModel) override;
    virtual void update(const gl::GameData& gameData) override {};
}