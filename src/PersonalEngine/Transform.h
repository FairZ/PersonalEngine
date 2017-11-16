#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "Component.h"
#include <vector>
#include <glm/glm.hpp>

/// \brief Component which handles transformations and parent-child hierarchy
class Transform : public Component
{
	friend class Entity;
	friend class Scene;
public:
	glm::vec3 GetPosition();
	glm::vec3 GetEulerRotation();
	glm::vec3 GetScale();
	glm::mat4x4 GetTransformationMatrix();
	std::weak_ptr<Entity> GetParent();

	void SetPosition(glm::vec3 _position);
	void SetEulerRotation(glm::vec3 _rotationInRadians);
	void SetScale(glm::vec3 _scale);

	/// \brief Set another entity to be this entity's child
	void AddChild(std::weak_ptr<Entity> _childEntity);

	/// \brief Translate the entity by the given vector
	void Translate(glm::vec3 _translation);
	/// \brief Rotate the entity by the given vector
	void Rotate(glm::vec3 _rotationInRadians);
	/// \brief Scale the entity by the given vector
	void Scale(glm::vec3 _scale);

private:
	std::weak_ptr<Entity> m_parent;
	std::vector<std::weak_ptr<Entity>> m_children;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4x4 m_transformationMatrix;

	void Destroy();

};

#endif