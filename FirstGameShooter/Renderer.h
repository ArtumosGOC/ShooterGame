// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

class Renderer {
public:
    void render(sf::RenderWindow& window, const Map& map, const Player& player, sf::RenderStates& state, sf::VertexArray& lines, sf::Text& fpsText);
};

#endif // RENDERER_H