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
	glm::vec3 GetLeft();
	glm::vec3 GetUp();
	glm::mat4x4 GetTransformationMatrix();
	glm::mat4x4 GetTranslationMatrix();
	glm::mat4x4 GetRotationMatrix();
	std::weak_ptr<Entity> GetParent();

	/// \brief Set location in local space
	void SetLocalPosition(glm::vec3 _position);
	/// \brief Set rotation in local space
	void SetLocalRotation(glm::vec3 _rotationInRadians);
	/// \brief Set scale in local space
	void SetLocalScale(glm::vec3 _scale);

	/// \brief Set location in world space
	void SetPosition(glm::vec3 _position);
	/// \brief Set rotation in world space
	void SetRotation(glm::vec3 _rotationInRadians);
	/// \brief Set scale in world space
	void SetScale(glm::vec3 _scale);

	void AddParent(std::weak_ptr<Entity> _childEntity);

	void AddChild(std::weak_ptr<Entity> _childEntity);

	void DetachChildren();

	void DetachFromParent();

	/// \brief Translate the entity by the given vector in world space
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