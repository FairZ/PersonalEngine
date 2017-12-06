#include "Camera.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Transform.h"

std::weak_ptr<Camera> Camera::mainCamera;

void Camera::SetFOV(float _FOV)
{
	m_fieldOfView = glm::radians(_FOV);
}

void Camera::SetOrthographic(bool _orthographic)
{
	m_orthographic = _orthographic;
}

void Camera::SetNearClipPlane(float _nearClipPlane)
{
	m_nearClipPlane = _nearClipPlane;
}

void Camera::SetFarClipPlane(float _farClipPlane)
{
	m_farClipPlane = _farClipPlane;
}

void Camera::SetAsMainCamera()
{
	Camera::mainCamera = m_entity->GetComponent<Camera>();
}

void Camera::CalculateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective<float>(m_fieldOfView,(float)Window::GetWidth()/(float)Window::GetHeight(),m_nearClipPlane,m_farClipPlane);
}

void Camera::CalculateViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_entity->m_transform->GetPosition(),m_entity->m_transform->GetPosition()+m_entity->m_transform->GetForward(),m_entity->m_transform->GetUp());
}