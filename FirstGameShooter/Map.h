// Map.h
#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <SFML/System.hpp>

enum class WallTexture {
    Smiley,
    Red,
    Bush,
    Sky,
    Pink,
    Wallpaper,
    Dirt,
    Exit,
};

class Map {
public:
    static const int mapWidth = 24;
    static const int mapHeight = 24;
    static const std::unordered_map<char, WallTexture> wallTypes;
    static const char worldMap[];

    char getTile(int x, int y) const;
    bool mapCheck() const;
    bool canMove(sf::Vector2f position, sf::Vector2f size) const;
};

#endif // MAP_H