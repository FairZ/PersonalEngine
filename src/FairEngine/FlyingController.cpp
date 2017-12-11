#include "FlyingController.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void FlyingController::Awake()
{
	m_moveVector = glm::vec3(0);
	m_speed = 50.0f;
	m_rotSpeed = 0.1f;
}

void FlyingController::Start()
{
	SetReferences();
}

void FlyingController::SetReferences()
{
	m_transform = m_entity->m_transform;
	m_rb = m_entity->GetComponent<RigidBody>();
}

void FlyingController::FixedUpdate()
{
	//create a movement vector to decide which direction to accelerate in based on inputs
	m_moveVector = glm::vec3(0);

	if(Input::GetKey('w'))
	{
		m_moveVector += m_transform.lock()->GetForward();
	}
	if(Input::GetKey('s'))
	{
		m_moveVector -= m_transform.lock()->GetForward();
	}
	if(Input::GetKey('a'))
	{
		m_moveVector += m_transform.lock()->GetLeft();
	}
	if(Input::GetKey('d'))
	{
		m_moveVector -= m_transform.lock()->GetLeft();
	}
	if(Input::GetKey(' '))
	{
		m_moveVector += m_transform.lock()->GetUp();
	}
	if(Input::GetKey('z'))
	{
		m_moveVector -= m_transform.lock()->GetUp();
	}
	
	//add a force in the movement vector's direction
	if(m_moveVector != glm::vec3(0) && !m_rb.expired())
	{
		m_moveVector = glm::normalize(m_moveVector);
		m_rb.lock()->AddForce(m_moveVector*Time::GetFixedDeltaTimeSec()*m_speed);
	}
}

void FlyingController::Update()
{
	//rotate around the x and y axis
	m_transform.lock()->Rotate(glm::vec3(0, Input::GetMouseXDiff()*Time::GetDeltaTimeSec()*m_rotSpeed, 0));
	m_transform.lock()->Rotate(glm::vec3(Input::GetMouseYDiff()*Time::GetDeltaTimeSec()*m_rotSpeed, 0, 0));
}