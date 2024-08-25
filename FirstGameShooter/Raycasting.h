#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Raycasting
{
public:
	Raycasting();
	~Raycasting();

	void renderRaycasting(RenderTarget* target);
	void updateRaycasting(RenderTarget& target);

	bool endGame = 0b0;

	void pollEvents(RenderTarget* target);
	RectangleShape vRaycasting;
};

