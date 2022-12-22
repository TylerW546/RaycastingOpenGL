#include "Character.hpp"

Character::Character(Point<float> position = Point<float>(), float angle = 0, float walkSpeed = 1, float runSpeed = 2, float maxHealth = 100, float maxStamina = 100) :
    position_(position),
    angle_(angle),
    walkSpeed_(walkSpeed),
    runSpeed_(runSpeed),
    maxHealth_(maxHealth),
    maxStamina_(maxStamina)
{}

void Character::update(const gl::GameData& gameData) {
    std::cout << "Updating" << "\n";
    position_.x += std::cos(angle_) * walkSpeed_;
    position_.y += std::sin(angle_) * walkSpeed_;
    
}