#include "Weapon.h"

Weapon::Weapon() : isShooting(false), shootCooldown(0.5f), shootTimer(0.0f) {
    texture.loadFromFile("Data\\Texture\\bullet.png");
    sprite.setTexture(texture);
    sprite.setPosition(640, 360); // Center of the screen
}

void Weapon::shoot(sf::RenderTarget& window) {
    if (shootTimer <= 0.1f) {
        isShooting = true;
        shootTimer = shootCooldown;

    }
	window.draw(sprite);
}

void Weapon::update(float dt) {
    if (shootTimer > 0.1f) {
        shootTimer -= dt;
    }
    else {
        isShooting = false;
    }
}