#include "Camera.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

std::weak_ptr<Camera> Camera::mainCamera;

void Camera::SetAsMainCamera()
{
	Camera::mainCamera = m_entity->GetComponent<Camera>();
	CalculateProjectionMatrix();
}

void Camera::CalculateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective<float>(m_fieldOFView,(float)(Window::GetWidth()/Window::GetHeight()),m_nearClipPlane,m_farClipPlane);
}