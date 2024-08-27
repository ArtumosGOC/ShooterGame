#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

class Weapon {
public:
    Weapon();
    void shoot(sf::RenderTarget& window);
    void update(float dt);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool isShooting;
    float shootCooldown;
    float shootTimer;
};

#endif // WEAPON_H