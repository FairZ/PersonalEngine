#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_
#include "Component.h"
#include "glm/glm.hpp"

class Transform;

class RigidBody : public Component
{
public:
	void SetVelocity(glm::vec3 _velocity);
	void SetAcceleration(glm::vec3 _acceleration);
	void SetGravity(glm::vec3 _gravity);
	void SetDrag(float _drag);
	void AddImpulse(glm::vec3 _impulse);
	void AddForce(glm::vec3 _force);

private:
	void Awake();
	void Update();

	float m_drag;
	float m_mass;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	glm::vec3 m_gravity;

	std::weak_ptr<Transform> m_transform;

};

#endif