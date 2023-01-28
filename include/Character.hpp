#include "Util.hpp"
#include "glBase/Entity.hpp"
#include "glBase/Texture.hpp"
#include "Raycaster.hpp"

#include <list>
#include <iostream>

class Character : public gl::Entity {
    // Position in world
    Point<float> position_;
    Point<float> velocity_;
    Point<float> acceleration_;

    float angle_;

    float walkSpeed_;
    float runSpeed_;

    // Abilities
    int numAbilities_;
    std::list<float> abilityMaxCooldowns_;
    std::list<float> abilityCooldowns_;

    // Health
    float maxHealth_;
    float health_;
    float extraHealth_;
    float shield_;

    float maxStamina_;
    float stamina_;

    gl::Texture_base* icon_;  

    public:
    Character(Point<float> position = Point<float>(), float angle = 0, float walkSpeed = 1, float runSpeed = 2, float maxHealth = 100, float maxStamina = 100);
    Point<float> getPosition() {return position_;}
    float getAngle() {return angle_;}
    
    std::list<float> getAbilityMaxCooldowns() {return abilityMaxCooldowns_;}
    std::list<float> getAbilityCooldowns() {return abilityCooldowns_;}

    std::list<float> getHealthData() {return std::list<float>{maxHealth_, health_, extraHealth_, shield_};}

    virtual void update(const gl::GameData& gameData) override;
};