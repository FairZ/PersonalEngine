#include "Window.h"
#include "Camera.h"
#include <GL/glew.h>

int Window::m_width;
int Window::m_height;

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
	glViewport(0, 0, m_width, m_height);
	Camera::mainCamera.lock()->CalculateProjectionMatrix();
	//TODO add aspect ratio switching either by linking to cameras or using gluPerspective
}
