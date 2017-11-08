#include "Transform.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Transform::GetPosition()
{
	return m_position;
}

glm::vec3 Transform::GetEulerRotation()
{
	return m_rotation;
}

glm::vec3 Transform::GetScale()
{
	return m_scale;
}

glm::mat4x4 Transform::GetTransformationMatrix()
{
	m_parent.expired() ? m_transformationMatrix = glm::mat4(1) : m_transformationMatrix = m_parent.lock()->m_transform->GetTransformationMatrix();
	m_transformationMatrix = glm::translate(m_transformationMatrix, m_position);
	m_transformationMatrix = glm::rotate(m_transformationMatrix, m_rotation.z, glm::vec3(0, 0, 1.0f));
	m_transformationMatrix = glm::rotate(m_transformationMatrix, m_rotation.y, glm::vec3(0, 1.0f, 0));
	m_transformationMatrix = glm::rotate(m_transformationMatrix, m_rotation.x, glm::vec3(1.0f, 0, 0));
	m_transformationMatrix = glm::scale(m_transformationMatrix, m_scale);
	return m_transformationMatrix;
}

std::weak_ptr<Entity> Transform::GetParent()
{
	return m_parent;
}

void Transform::SetPosition(glm::vec3 _position)
{
	m_position = _position;
}

void Transform::SetEulerRotation(glm::vec3 _rotationInRadians)
{
	m_rotation = _rotationInRadians;
}

void Transform::SetScale(glm::vec3 _scale)
{
	m_scale = _scale;
}

void Transform::AddChild(std::weak_ptr<Entity> _childEntity)
{
	m_children.push_back(_childEntity);
}

void Transform::Translate(glm::vec3 _translation)
{
	m_position += _translation;
}

void Transform::Rotate(glm::vec3 _rotationInRadians)
{
	m_rotation += _rotationInRadians;
	if(m_rotation.x >= 6.2831f)
		m_rotation.x -= 6.2831f;
	if(m_rotation.y >= 6.2831f)
		m_rotation.y -= 6.2831f;
	if(m_rotation.z >= 6.2831f)
		m_rotation.z -= 6.2831f;
}

void Transform::Scale(glm::vec3 _scale)
{
	m_scale *= _scale;
}