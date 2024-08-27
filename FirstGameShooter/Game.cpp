// Game.cpp
#include "Game.h"
#include <stdio.h>

Game::Game()
    : window(sf::VideoMode(1280 + 1, 720), "ShooterGame"), lines(sf::Lines, 18 * 1280), dt_counter(0.0f), frame_counter(0), frame_time_micro(0), hasFocus(true) {
    window.setSize(sf::Vector2u(1280, 720));
    window.setFramerateLimit(60);

    if (!font.loadFromFile("Data\\Font\\opensans.ttf")) {
        fprintf(stderr, "Cannot open font!\n");
        exit(EXIT_FAILURE);
    }

    if (!texture.loadFromFile("Data\\Texture\\walls.png")) {
        fprintf(stderr, "Cannot open texture!\n");
        exit(EXIT_FAILURE);
    }
    
    state.texture = &texture;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);

    if (!map.mapCheck()) {
        fprintf(stderr, "Map is invalid!\n");
        exit(EXIT_FAILURE);
    }
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::GainedFocus) {
            hasFocus = true;
        }
        else if (event.type == sf::Event::LostFocus) {
            hasFocus = false;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
            player.shoot(window);
			printf("Shoot\n");
        }
    }
}
void Game::update(float dt) {
    player.weapon.update(dt);
    if (hasFocus) {
        using kb = sf::Keyboard;
        using ms = sf::Mouse;
        shit_value = 0.8f;

        float moveForward = 0.0f;
		if (kb::isKeyPressed(kb::LShift)){
            if (kb::isKeyPressed(kb::W)) {
                moveForward = 1.0f;
            }
            else if (kb::isKeyPressed(kb::S)) {
                moveForward = -1.0f;
            }
            if(player.getmoveSpeed() !=0)
                 player.move(moveForward, dt, map, 1.5);
            else
                player.move(moveForward, dt, map, 1);
		}
        else
        {
            if (kb::isKeyPressed(kb::W)) {
                moveForward = 1.0f;
            }
            else if (kb::isKeyPressed(kb::S)) {
                moveForward = -1.0f;
            }
            player.move(moveForward, dt, map, shit_value);
        }
		

        float moveSideways = 0.0f;
        if (kb::isKeyPressed(kb::A)) {
            moveSideways = -1.0f * shit_value;
        }
        else if (kb::isKeyPressed(kb::D)) {
            moveSideways = 1.0f * shit_value;
        }
        player.strafe(moveSideways, dt, map);

        // Process mouse movement
        sf::Vector2i mousePosition = ms::getPosition(window);
        sf::Vector2i windowCenter(window.getSize().x / 2, window.getSize().y / 2);
        sf::Vector2i mouseDelta = mousePosition - windowCenter;

        float rotateDirection = static_cast<float>(mouseDelta.x) * 0.01f; // Adjust sensitivity as needed
        player.rotate(rotateDirection, dt);

        // Reset mouse position to the center of the window
        ms::setPosition(windowCenter, window);
    }

    dt_counter += dt;
    ++frame_counter;

    if (dt_counter >= 0.1f) {
        float fps = (float)frame_counter / dt_counter;
        frame_time_micro /= frame_counter;
        snprintf(frameInfoString, sizeof(frameInfoString), "FPS: %3.1f Frame time: %6ld", fps, frame_time_micro);
        fpsText.setString(frameInfoString);
        dt_counter = 0.0f;
        frame_counter = 0;
        frame_time_micro = 0;
    }
}

void Game::render() {
    renderer.render(window, map, player, state, lines, fpsText);
    frame_time_micro += clock.getElapsedTime().asMicroseconds();
}