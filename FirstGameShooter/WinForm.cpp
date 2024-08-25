#include "WinForm.h"

WinForm::WinForm(int width, int height)
{
	this->initVariables(width, height);
	this->initWindow();
}
WinForm::~WinForm()
{
	delete this->window;
}

void WinForm::initVariables(int width, int height)
{
	player = new Player();
	this->title = title;
	this->width = width;
	this->height = height;

	this->event = Event();	
}
const bool WinForm::getIsOpen() const
{
	return this->window->isOpen();
}
void WinForm::initWindow()
{

	this->videoMode.width = this->width;
	this->videoMode.height = this->height;
	this->videoMode.bitsPerPixel = 32;

	this->window = new RenderWindow(this->videoMode, this->title, Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(0b0);
}

void WinForm::update()
{

	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == Event::Closed)
			this->window->close();
	}
	this->player->updatePlayer(*this->window);
}

void WinForm::render()
{
	this->window->clear(Color::Blue);
	this->player->renderPlayer(this->window);
	this->window->display();
}
