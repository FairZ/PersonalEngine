#ifndef _FLYINGCONTROLLER_H_
#define _FLYINGCONTROLLER_H_
#include "Component.h"
#include <memory>
#include <glm/glm.hpp>

class Transform;

class FlyingController : public Component
{
public:

private:
	void Awake();
	void Start();
	void Update();
	void SetReferences();

	std::weak_ptr<Transform> m_transform;

	float m_speed;
	float m_rotSpeed;
	glm::vec3 m_moveVector;
};


#endif