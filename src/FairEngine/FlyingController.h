#ifndef _FLYINGCONTROLLER_H_
#define _FLYINGCONTROLLER_H_
#include "Component.h"
#include <memory>
#include <glm/glm.hpp>

class Transform;
class RigidBody;

/// \brief Moves the Entity around using forces and rotations
///
/// WASD for z/x axis movement, Space and Z for y axis movement
/// Mouse controls rotation
class FlyingController : public Component
{
public:

private:
	void Awake();
	void Start();
	void Update();
	void FixedUpdate();
	void SetReferences();

	std::weak_ptr<Transform> m_transform;
	std::weak_ptr<RigidBody> m_rb;

	float m_speed;
	float m_rotSpeed;
	glm::vec3 m_moveVector;
};


#endif