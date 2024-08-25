#include<iostream>
#include "WinForm.h"

using namespace std;

int main(int argc, char* argv[])
{
	const wchar_t* title = L"First Game Shooter";

	WinForm form(800, 600);
	form.title = title;

	while (form.getIsOpen())
	{
		form.update();
		form.render();
	}
}