// Map.cpp
#include "Map.h"
#include <stdio.h>

const std::unordered_map<char, WallTexture> Map::wallTypes{
    {'#', WallTexture::Pink},
    {'=', WallTexture::Dirt},
    {'M', WallTexture::Wallpaper},
    {'N', WallTexture::Bush},
    {'~', WallTexture::Sky},
    {'!', WallTexture::Red},
    {'@', WallTexture::Smiley},
    {'^', WallTexture::Exit},
};

const char Map::worldMap[] =
"~~~~~~~~~~~~~~~~MMM@MMMM"
"~..............=M......M"
"~..............=M......M"
"~..............=@......@"
"~..............=M......M"
"~....N......N..........M"
"~..............=MMM@MM.M"
"~..............======M.M"
"~..............=MMMMMM.M"
"~..............=M......M"
"~...N....N.....=M..N..M#"
"~.....................M#"
"~..............=M..N..M#"
"~..............=M.....M#"
"~...........N..=MMMMM.M#"
"~..............======.=#"
"#.!!!!!!.!!!!!!........#"
"#.!....!.!..........=..#"
"#.!.N..!.!..==..=...=..#"
"#...........==..==..=..#"
"#.!!!!!!.!..==.........#"
"#.######.#..==....=....#"
"N......................^"
"########################";

char Map::getTile(int x, int y) const {
    return worldMap[y * mapWidth + x];
}

bool Map::mapCheck() const {
    int mapSize = sizeof(worldMap) - 1;
    if (mapSize != mapWidth * mapHeight) {
        fprintf(stderr, "Map size(%d) is not mapWidth * mapHeight(%d)\n", mapSize, mapWidth * mapHeight);
        return false;
    }

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            char tile = getTile(x, y);
            if (tile != '.' && wallTypes.find(tile) == wallTypes.end()) {
                fprintf(stderr, "map tile at [%3d,%3d] has an unknown tile type(%c)\n", x, y, tile);
                return false;
            }
            if ((y == 0 || x == 0 || y == mapHeight - 1 || x == mapWidth - 1) && tile == '.') {
                fprintf(stderr, "map edge at [%3d,%3d] is a floor (should be wall)\n", x, y);
                return false;
            }
        }
    }
    return true;
}

bool Map::canMove(sf::Vector2f position, sf::Vector2f size) const {
    sf::Vector2i upper_left(position - size / 2.0f);
    sf::Vector2i lower_right(position + size / 2.0f);
    if (upper_left.x < 0 || upper_left.y < 0 || lower_right.x >= mapWidth || lower_right.y >= mapHeight) {
        return false;
    }
    for (int y = upper_left.y; y <= lower_right.y; ++y) {
        for (int x = upper_left.x; x <= lower_right.x; ++x) {
            if (getTile(x, y) != '.') {
                return false;
            }
        }
    }
    return true;
}