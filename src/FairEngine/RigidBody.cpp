#include "RigidBody.h"
#include "Transform.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void RigidBody::SetLinearVelocity(glm::vec3 _velocity)
{
	m_linearVelocity = _velocity;
}

void RigidBody::SetLinearAcceleration(glm::vec3 _acceleration)
{
	m_linearAcceleration = _acceleration;
}

void RigidBody::SetInertiaTensor(glm::mat3 _inertiaTensor)
{
	m_inverseInertiaTensor = glm::inverse(_inertiaTensor);
}

void RigidBody::SetGravity(glm::vec3 _gravity)
{
	m_gravity = _gravity;
}

void RigidBody::SetDrag(float _drag)
{
	m_drag = _drag;
}

void RigidBody::SetMass(float _mass)
{
	m_mass = _mass;
}

void RigidBody::AddForce(glm::vec3 _force)
{
	m_forceAccumulator += _force;
}

void RigidBody::AddForceAtWorldPosition(glm::vec3 _force, glm::vec3 _position)
{
	glm::vec3 localPosition = _position - m_transform.lock()->GetPosition();

	m_forceAccumulator += _force;
	m_torqueAccumulator += glm::cross(localPosition, _force);
}

void RigidBody::AddForceAtBodyPosition(glm::vec3 _force, glm::vec3 _position)
{
	m_forceAccumulator += _force;
	m_torqueAccumulator += glm::cross(_position, _force);
}

void RigidBody::Awake()
{
	m_drag = 0.99f;
	m_mass = 1.0f;
	m_gravity = glm::vec3(0, -9.81, 0); 
}

void RigidBody::Start()
{
	SetReferences();

	glm::mat3 inertiaTensor(0);
	inertiaTensor[0][0] = (m_mass*0.4f);
	inertiaTensor[1][1] = (m_mass*0.4f);
	inertiaTensor[2][2] = (m_mass*0.4f);
	SetInertiaTensor(inertiaTensor);
}

void RigidBody::SetReferences()
{
	m_transform = m_entity->m_transform;
}

void RigidBody::FixedUpdate()
{
	//add up accelerations and add it to the velocitry
	m_linearAcceleration = m_gravity;
	m_linearAcceleration += m_forceAccumulator / m_mass;
	m_linearVelocity += m_linearAcceleration * Time::GetFixedDeltaTimeSec();
	//add up the angular velocity
	glm::mat3 rotationMatrix = m_transform.lock()->GetRotationMatrix();
    m_angularVelocity += (m_inverseInertiaTensor * rotationMatrix) * m_torqueAccumulator * Time::GetFixedDeltaTimeSec();

	//apply drag
	m_linearVelocity *= std::pow(m_drag, Time::GetFixedDeltaTimeSec());
	m_angularVelocity *= std::pow(m_drag, Time::GetFixedDeltaTimeSec());

	//translate and rotate by the calculated values
	m_transform.lock()->Translate(m_linearVelocity * Time::GetFixedDeltaTimeSec());
	m_transform.lock()->Rotate(m_angularVelocity * Time::GetFixedDeltaTimeSec());

	//reset the accumulators
	m_forceAccumulator = glm::vec3();
	m_torqueAccumulator = glm::vec3();
}