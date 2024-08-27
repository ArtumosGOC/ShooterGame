// Game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Renderer.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Map map;
    Player player;
    Renderer renderer;
    sf::Font font;
    sf::Texture texture;
    sf::RenderStates state;
    sf::VertexArray lines;
    sf::Text fpsText;
    sf::Clock clock;
    char frameInfoString[sizeof("FPS: *****.*, Frame time: ******")];
    float dt_counter;
    float shit_value = 0.8f;
    int frame_counter;
    int64_t frame_time_micro;
    bool hasFocus;

    void handleEvents();
    void update(float dt);
    void render();
};

#endif // GAME_H