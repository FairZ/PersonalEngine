#include "Transform.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

glm::vec3 Transform::GetLocalPosition()
{
	return m_position;
}

glm::vec3 Transform::GetLocalRotation()
{
	return m_rotation;
}

glm::vec3 Transform::GetLocalScale()
{
	return m_scale;
}

glm::vec3 Transform::GetPosition()
{
	return GetTransformationMatrix()*glm::vec4(0,0,0,1);
}

glm::vec3 Transform::GetScale()
{
	glm::vec3 scale = m_scale;
	if(!GetParent().expired())
	{
		scale *= GetParent().lock()->m_transform->GetScale();
	}
	return scale;
}

glm::vec3 Transform::GetRotation()
{
	glm::vec3 rotation = m_rotation;
	if(!GetParent().expired())
	{
		rotation += GetParent().lock()->m_transform->GetRotation();
	}
	return rotation;
}

glm::vec3 Transform::GetForward()
{
	return  GetRotationMatrix() * glm::vec4(0,0,1,1);
}

glm::vec3 Transform::GetLeft()
{
	return GetRotationMatrix() * glm::vec4(1,0,0,1);
}

glm::vec3 Transform::GetUp()
{
	return GetRotationMatrix() * glm::vec4(0,1,0,1);
}

glm::mat4x4 Transform::GetTransformationMatrix()
{
	//recursively move up the heirarchy to include the transformation of parents or start from an identity matrix if there is no parent
	m_parent.expired() ? m_transformationMatrix = glm::mat4(1) : m_transformationMatrix = m_parent.lock()->m_transform->GetTransformationMatrix();
	m_transformationMatrix = glm::translate(m_transformationMatrix, m_position);
	m_transformationMatrix = glm::rotate(m_transformationMatrix, m_rotation.z, glm::vec3(0, 0, 1.0f));
	m_transformationMatrix = glm::rotate(m_transformationMatrix, m_rotation.y, glm::vec3(0, 1.0f, 0));
	m_transformationMatrix = glm::rotate(m_transformationMatrix, m_rotation.x, glm::vec3(1.0f, 0, 0));
	m_transformationMatrix = glm::scale(m_transformationMatrix, m_scale);
	return m_transformationMatrix;
}

glm::mat4x4 Transform::GetTranslationMatrix()
{
	glm::mat4 translation(1);
	//recursively move up the heirarchy to include the transformation of parents or start from an identity matrix if there is no parent
	if (!m_parent.expired())
	{
		translation = m_parent.lock()->m_transform->GetTranslationMatrix();
	}
	translation = glm::translate(translation, m_position);

	return translation;
}

glm::mat4x4 Transform::GetRotationMatrix()
{
	glm::mat4x4 retVal(1);
	if (!m_parent.expired())
	{
		retVal = m_parent.lock()->m_transform->GetRotationMatrix();
	}
	retVal = glm::rotate(retVal, m_rotation.z, glm::vec3(0, 0, 1.0f));
	retVal = glm::rotate(retVal, m_rotation.y, glm::vec3(0, 1.0f, 0));
	retVal = glm::rotate(retVal, m_rotation.x, glm::vec3(1.0f, 0, 0));

	return retVal;
}

std::weak_ptr<Entity> Transform::GetParent()
{
	return m_parent;
}

void Transform::SetLocalPosition(glm::vec3 _position)
{
	m_position = _position;
}

void Transform::SetLocalRotation(glm::vec3 _rotationInRadians)
{
	m_rotation = _rotationInRadians;
}

void Transform::SetLocalScale(glm::vec3 _scale)
{
	m_scale = _scale;
}

void Transform::SetPosition(glm::vec3 _position)
{
	if(!GetParent().expired())
	{
		m_position = glm::inverse(GetParent().lock()->m_transform->GetTransformationMatrix()) * glm::vec4(_position, 1);
	}
	else
	{
		m_position = _position;
	}
}

void Transform::SetRotation(glm::vec3 _rotationInRadians)
{
	if(!GetParent().expired())
	{
		m_rotation = _rotationInRadians - GetParent().lock()->m_transform->GetRotation();
	}
	else
	{
		m_rotation = _rotationInRadians;
	}
}

void Transform::SetScale(glm::vec3 _scale)
{
	if(!GetParent().expired())
	{
		m_scale = _scale - GetParent().lock()->m_transform->GetScale();
	}
	else
	{
		m_scale = _scale;
	}
}

void Transform::AddParent(std::weak_ptr<Entity> _parentEntity)
{
	DetachFromParent();
	m_parent = _parentEntity;
	_parentEntity.lock()->m_transform->m_children.push_back(Entity::FindEntity(m_entity->GetName()));
}

void Transform::AddChild(std::weak_ptr<Entity> _childEntity)
{
	m_children.push_back(_childEntity);
	_childEntity.lock()->m_transform->m_parent = Entity::FindEntity(m_entity->GetName());
}

void Transform::DetachChildren()
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		std::weak_ptr<Transform> child = m_children.at(i).lock()->m_transform;
		if(!child.expired())
		{
			child.lock()->SetLocalPosition(child.lock()->GetPosition());
			child.lock()->SetLocalRotation(child.lock()->GetRotation());
			child.lock()->SetLocalScale(child.lock()->GetScale());
			child.lock()->m_parent.reset();
		}
	}
	m_children.clear();
}

void Transform::DetachFromParent()
{
	if(!m_parent.expired())
	{
		SetLocalPosition(GetPosition());
		SetLocalRotation(GetRotation());
		SetLocalScale(GetScale());
	}
	m_parent.reset();
}

void Transform::Translate(glm::vec3 _translation)
{
	if (!m_parent.expired())
	{
		SetPosition(GetPosition()+_translation);
	}
	else
		m_position += _translation;
}

void Transform::Rotate(glm::vec3 _rotationInRadians)
{
	m_rotation += _rotationInRadians;
}

void Transform::Scale(glm::vec3 _scale)
{
	m_scale *= _scale;
}

void Transform::Destroy()
{
	DetachChildren();
}