// Renderer.cpp
#include "Renderer.h"

void Renderer::render(sf::RenderWindow& window, const Map& map, const Player& player, sf::RenderStates& state, sf::VertexArray& lines, sf::Text& fpsText) {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const float cameraHeight = 0.66f;
    const int texture_size = 512;
    const int texture_wall_size = 128;

    lines.resize(0);

    for (int x = 0; x < screenWidth; ++x) {
        float cameraX = 2 * x / (float)screenWidth - 1.0f;
        sf::Vector2f rayPos = player.position;
        sf::Vector2f rayDir = player.direction + player.plane * cameraX;

        sf::Vector2f deltaDist(
            sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
            sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y))
        );

        sf::Vector2i mapPos(rayPos);
        sf::Vector2i step;
        sf::Vector2f sideDist;

        if (rayDir.x < 0.0f) {
            step.x = -1;
            sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
        }
        else {
            step.x = 1;
            sideDist.x = (mapPos.x + 1.0f - rayPos.x) * deltaDist.x;
        }
        if (rayDir.y < 0.0f) {
            step.y = -1;
            sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
        }
        else {
            step.y = 1;
            sideDist.y = (mapPos.y + 1.0f - rayPos.y) * deltaDist.y;
        }

        char tile = '.';
        bool horizontal;
        float perpWallDist = 0.0f;
        int wallHeight;
        int ceilingPixel = 0;
        int groundPixel = screenHeight;

        sf::Color color1 = sf::Color::Green;
        sf::Color color2 = sf::Color::Cyan;
        sf::Color color = ((mapPos.x % 2 == 0 && mapPos.y % 2 == 0) || (mapPos.x % 2 == 1 && mapPos.y % 2 == 1)) ? color1 : color2;

        while (tile == '.') {
            if (sideDist.x < sideDist.y) {
                sideDist.x += deltaDist.x;
                mapPos.x += step.x;
                horizontal = true;
                perpWallDist = (mapPos.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
            }
            else {
                sideDist.y += deltaDist.y;
                mapPos.y += step.y;
                horizontal = false;
                perpWallDist = (mapPos.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;
            }

            wallHeight = screenHeight / perpWallDist;

            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(385.0f, 129.0f)));
            groundPixel = int(wallHeight * cameraHeight + screenHeight * 0.5f);
            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(385.0f, 129.0f)));

            sf::Color color_c = color;
            color_c.r /= 2;
            color_c.g /= 2;
            color_c.b /= 2;

            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(385.0f, 129.0f)));
            ceilingPixel = int(-wallHeight * (1.0f - cameraHeight) + screenHeight * 0.5f);
            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(385.0f, 129.0f)));

            color = (color == color1) ? color2 : color1;
            tile = map.getTile(mapPos.x, mapPos.y);
        }

        int drawStart = ceilingPixel;
        int drawEnd = groundPixel;

        int wallTextureNum = (int)Map::wallTypes.find(tile)->second;
        sf::Vector2i texture_coords(
            wallTextureNum * texture_wall_size % texture_size,
            wallTextureNum * texture_wall_size / texture_size * texture_wall_size
        );

        float wall_x;
        if (horizontal) {
            wall_x = rayPos.y + perpWallDist * rayDir.y;
        }
        else {
            wall_x = rayPos.x + perpWallDist * rayDir.x;
        }
        wall_x -= floor(wall_x);

        int tex_x = int(wall_x * float(texture_wall_size));
        if ((horizontal && rayDir.x <= 0) || (!horizontal && rayDir.y >= 0)) {
            tex_x = texture_wall_size - tex_x - 1;
        }

        texture_coords.x += tex_x;

        color = sf::Color::White;
        if (horizontal) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        lines.append(sf::Vertex(
            sf::Vector2f((float)x, (float)drawStart),
            color,
            sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1)
        ));
        lines.append(sf::Vertex(
            sf::Vector2f((float)x, (float)drawEnd),
            color,
            sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + texture_wall_size - 1))
        ));
    }

    window.clear();
    window.draw(lines, state);
    renderWeapon(window, player);
    window.draw(fpsText);
    window.display();
}

void Renderer::renderWeapon(sf::RenderWindow& window, const Player& player)
{
	Player p = player;
	p.shoot(window);
}
