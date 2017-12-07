#include "FlyingController.h"
#include "Transform.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void FlyingController::Awake()
{
	m_moveVector = glm::vec3(0);
	m_speed = 5.0f;
	m_rotSpeed = 0.1f;
}

void FlyingController::Start()
{
	m_transform = m_entity->m_transform;
}

void FlyingController::Update()
{
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

	m_transform.lock()->Rotate(glm::vec3(0, Input::GetMouseXDiff()*Time::GetDeltaTimeSec()*m_rotSpeed, 0));


	m_transform.lock()->Rotate(glm::vec3(Input::GetMouseYDiff()*Time::GetDeltaTimeSec()*m_rotSpeed, 0, 0));
	
	if(m_moveVector != glm::vec3(0))
	{
		m_moveVector = glm::normalize(m_moveVector);
		m_transform.lock()->Translate(m_moveVector*m_speed*Time::GetDeltaTimeSec());
	}
}