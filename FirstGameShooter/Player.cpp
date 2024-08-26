// Player.cpp
#include "Player.h"
#include <cmath>

float Player::getmoveSpeed()
{
    return moveSpeed;
}

Player::Player()
    : position(2.5f, 2.0f), direction(0.0f, 1.0f), plane(-0.66f, 0.0f), size(0.375f, 0.375f), moveSpeed(5.0f), rotateSpeed(3.0f) {}

void Player::move(float moveForward, float dt, const Map& map, float shift) {
    if (moveForward != 0.0f) {
        sf::Vector2f moveVec = direction * moveSpeed * moveForward * dt;
        if (map.canMove(sf::Vector2f(position.x + moveVec.x, position.y), size)) {
            position.x += moveVec.x * shift;
        }
        if (map.canMove(sf::Vector2f(position.x, position.y + moveVec.y), size)) {
            position.y += moveVec.y * shift;
        }
    }
}

void Player::rotate(float rotateDirection, float dt) {
    if (rotateDirection != 0.0f) {
        float rotation = rotateSpeed * rotateDirection * dt;
        direction = sf::Vector2f(
            direction.x * std::cos(rotation) - direction.y * std::sin(rotation),
            direction.x * std::sin(rotation) + direction.y * std::cos(rotation)
        );
        plane = sf::Vector2f(
            plane.x * std::cos(rotation) - plane.y * std::sin(rotation),
            plane.x * std::sin(rotation) + plane.y * std::cos(rotation)
        );
    }
}
void Player::strafe(float moveSideways, float dt, const Map& map) {
    if (moveSideways != 0.0f) {
        sf::Vector2f moveVec = plane * moveSpeed * moveSideways * dt;
        if (map.canMove(sf::Vector2f(position.x + moveVec.x, position.y), size)) {
            position.x += moveVec.x;
        }
        if (map.canMove(sf::Vector2f(position.x, position.y + moveVec.y), size)) {
            position.y += moveVec.y;
        }
    }
}