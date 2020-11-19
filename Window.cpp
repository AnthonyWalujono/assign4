#include "Window.h"

void Window::occupy(int time_needed)
{
	occupied = true;
	this->time_needed = time_needed;
	idle = 0;
}

void Window::update()
{
	if (occupied) {
		if (--time_needed == 0) {
			occupied = false;
		}
	}
	else {
		++idle;
	}
}
