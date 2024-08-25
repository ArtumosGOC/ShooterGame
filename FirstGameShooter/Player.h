#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>

using namespace sf;
using namespace std;

class Player
{
public:
	Player();
	~Player();

	void renderPlayer(RenderTarget* target);
	void updatePlayer(RenderTarget& target);

	bool endGame = 0b0;

	void pollEvents(RenderTarget* target);
	RectangleShape vPlayer;

private:
	void initVariables();
	void initPlayer();

	unsigned int points;
	unsigned int maxBullets;
	int Health;
	int maxHealth;
	float velocity;


	Event event;

	vector<RectangleShape> vPlayers;
};