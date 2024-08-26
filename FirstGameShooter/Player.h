// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include "Map.h"

class Player {
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::Vector2f plane;
    sf::Vector2f size;
    float moveSpeed;
    float rotateSpeed;

    Player();

    void move(float moveForward, float dt, const Map& map);
    void rotate(float rotateDirection, float dt);
};

#endif // PLAYER_H