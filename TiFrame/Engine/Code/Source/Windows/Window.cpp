#include <Windows/Window.h>
using namespace Ti;



Window::Window()
{
	uim = nullptr;
}


Window::Window(UIManager * _uim)
{
	uim = _uim;
}

Window::~Window()
{
}