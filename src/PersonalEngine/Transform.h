#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "Component.h"
#include <vector>
#include <glm/glm.hpp>

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
	void SetEulerRotation(glm::vec3 _rotation);
	void SetScale(glm::vec3 _scale);
	void AddChild(std::weak_ptr<Entity> _childEntity);

	void Translate(glm::vec3 _translation);
	void Rotate(glm::vec3 _rotation);
	void Scale(glm::vec3 _scale);

private:
	std::weak_ptr<Entity> m_parent;
	std::vector<std::weak_ptr<Entity>> m_children;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4x4 m_transformationMatrix;

	void Update(){}//temp
	void Awake(){}//temp
	void Destroy(){}//temp

};

#endif