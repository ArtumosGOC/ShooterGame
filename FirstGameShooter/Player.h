// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include "Map.h"
#include "Weapon.h"

class Player {
public:
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::Vector2f plane;
    sf::Vector2f size;
    float moveSpeed;
    float rotateSpeed;

    Weapon weapon;
	
    float getmoveSpeed();
    Player();

    
    void move(float moveForward, float dt, const Map& map, float shift);
    void strafe(float moveSideways, float dt, const Map& map);
    void rotate(float rotateDirection, float dt);
    void shoot(sf::RenderTarget& window);
};
#endif // PLAYER_H