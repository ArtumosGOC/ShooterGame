#include "Player.h"

Player::Player()
{
	initVariables();
	initPlayer();

}

Player::~Player()
{
	delete this;
}
void Player::initVariables()
{
	this->points = 0;
	this->velocity = 3.f;
	this->maxBullets = 10;
	this->Health = 100;
	this->maxHealth = 100;
	this->endGame = false;
}

void Player::initPlayer()
{
	this->vPlayer.setPosition(400.f, 300.f);
	this->vPlayer.setSize(Vector2f(50.f, 50.f));
	this->vPlayer.setFillColor(Color::Green);
	this->vPlayer.setOutlineColor(Color::Black);

}

void Player::pollEvents(RenderTarget* target)
{

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->vPlayer.move(-1.f*velocity, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->vPlayer.move(1.f * velocity, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->vPlayer.move(0.f, -1.f * velocity);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->vPlayer.move(0.f, 1.f * velocity);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		new Player();
	}

}

void Player::renderPlayer(RenderTarget* target)
{
	target->draw(this->vPlayer);
}

void Player::updatePlayer(RenderTarget& target)
{
	this->pollEvents(&target);
	this->renderPlayer(&target);
}
