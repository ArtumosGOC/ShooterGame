// Game.cpp
#include "Game.h"
#include <stdio.h>

Game::Game()
    : window(sf::VideoMode(1280 + 1, 720), "Adventure 3D"), lines(sf::Lines, 18 * 1280), dt_counter(0.0f), frame_counter(0), frame_time_micro(0), hasFocus(true) {
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
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            hasFocus = false;
            break;
        case sf::Event::GainedFocus:
            hasFocus = true;
            break;
        default:
            break;
        }
    }
}

void Game::update(float dt) {
    if (hasFocus) {
        using kb = sf::Keyboard;

        float moveForward = 0.0f;
        if (kb::isKeyPressed(kb::Up)) {
            moveForward = 1.0f;
        }
        else if (kb::isKeyPressed(kb::Down)) {
            moveForward = -1.0f;
        }
        player.move(moveForward, dt, map);

        float rotateDirection = 0.0f;
        if (kb::isKeyPressed(kb::Left)) {
            rotateDirection = -1.0f;
        }
        else if (kb::isKeyPressed(kb::Right)) {
            rotateDirection = 1.0f;
        }
        player.rotate(rotateDirection, dt);
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