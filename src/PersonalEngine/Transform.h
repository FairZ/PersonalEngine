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
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	glm::vec3 GetLocalPosition();
	glm::vec3 GetLocalRotation();
	glm::vec3 GetLocalScale();
	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::mat4x4 GetTransformationMatrix();
	glm::mat4x4 GetRotationMatrix();
	std::weak_ptr<Entity> GetParent();

	void SetLocalPosition(glm::vec3 _position);
	void SetLocalRotation(glm::vec3 _rotationInRadians);
	void SetLocalScale(glm::vec3 _scale);

	void SetPosition(glm::vec3 _position);
	void SetRotation(glm::vec3 _rotationInRadians);
	void SetScale(glm::vec3 _scale);

	/// \brief Set another entity to be this entity's child
	void AddChild(std::weak_ptr<Entity> _childEntity);

	void DetachChildren();

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

	void Awake();
	void Destroy();

};

#endif