#include "RigidBody.h"
#include "Transform.h"
#include "Entity.h"
#include "Time.h"

void RigidBody::SetVelocity(glm::vec3 _velocity)
{
	m_velocity = _velocity;
}

void RigidBody::SetAcceleration(glm::vec3 _acceleration)
{
	m_acceleration = _acceleration;
}

void RigidBody::SetGravity(glm::vec3 _gravity)
{
	m_gravity = _gravity;
}

void RigidBody::SetDrag(float _drag)
{
	m_drag = _drag;
}

void RigidBody::AddImpulse(glm::vec3 _impulse)
{
	m_velocity += (_impulse / m_mass);
}

void RigidBody::AddForce(glm::vec3 _force)
{
	m_acceleration += (_force / m_mass);
}

void RigidBody::Awake()
{
	m_drag = 0.99f;
	m_mass = 1.0f;
	m_velocity = glm::vec3(0);
	m_acceleration = glm::vec3(0);
	m_gravity = glm::vec3(0,-1.0f,0);
	m_transform = m_entity->m_transform;
}

void RigidBody::Update()
{
	m_transform.lock()->Translate(m_velocity*Time::GetDeltaTimeSec());
	m_velocity += (m_acceleration * Time::GetDeltaTimeSec());
	m_velocity *= std::pow(m_drag , Time::GetDeltaTimeSec());
	m_acceleration = m_gravity;
}