#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_
#include "Component.h"
#include "glm/glm.hpp"

class Transform;

class RigidBody : public Component
{
public:
	void SetLinearVelocity(glm::vec3 _velocity);
	void SetLinearAcceleration(glm::vec3 _acceleration);
	void SetInertiaTensor(glm::mat3 _inertiaTensor);
	void SetGravity(glm::vec3 _gravity);
	void SetDrag(float _drag);
	void SetMass(float _mass);
	void AddForce(glm::vec3 _force);
	void AddForceAtWorldPosition(glm::vec3 _force, glm::vec3 _position);
	void AddForceAtBodyPosition(glm::vec3 _force, glm::vec3 _position);
	glm::vec3 GetLinearVelocity() { return m_linearVelocity; }
	glm::vec3 GetLinearAcceleration() { return m_linearAcceleration; }
	float GetMass() { return m_mass; }
	std::weak_ptr<Transform> GetTransform() { return m_transform; }

private:
	void Awake();
	void Start();
	void SetReferences();
	void FixedUpdate();

	float m_drag;
	float m_mass;
	glm::vec3 m_linearVelocity;
	glm::vec3 m_angularVelocity;
	glm::vec3 m_linearAcceleration;
	glm::vec3 m_angularAcceleration;
	glm::vec3 m_forceAccumulator;
	glm::vec3 m_torqueAccumulator;
	glm::vec3 m_gravity;
	glm::mat3 m_inverseInertiaTensor;

	std::weak_ptr<Transform> m_transform;

};

#endif