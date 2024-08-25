#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

using namespace sf;
using namespace std;

class WinForm
{
public:

	Player* player;

	WinForm(int width, int height);
	~WinForm();

	const bool getIsOpen() const;

	void update();
	void render();

	const wchar_t* title;

private:

	RenderWindow* window;
	VideoMode videoMode;
	Event event;
	
	int width;
	int height;

	void initVariables(int width, int height);
	void initWindow();

};

