#include "Window.h"
#include "Camera.h"
#include <GL/glew.h>

int Window::m_width = 800;
int Window::m_height = 600;

int Window::GetWidth()
{
	return m_width;
}

int Window::GetHeight()
{
	return m_height;
}

void Window::Resize(int _width, int _height)
{
	m_width = _width;
	m_height = _height;
	//resize viewport to ensure correct drawing
	glViewport(0, 0, m_width, m_height);
}
