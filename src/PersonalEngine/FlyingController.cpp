#include "FlyingController.h"
#include "Transform.h"
#include "Entity.h"
#include "Time.h"
#include "Input.h"

void FlyingController::Awake()
{
	m_transform = m_entity->m_transform;
	m_moveVector = glm::vec3(0);
	m_speed = 5.0f;
}

void FlyingController::Update()
{
	m_moveVector = glm::vec3(0);
	m_transform.lock()->SetForward(glm::vec3(0,0,-1));

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
		m_moveVector -= m_transform.lock()->GetRight();
	}
	if(Input::GetKey('d'))
	{
		m_moveVector += m_transform.lock()->GetRight();
	}
	if(Input::GetKey(' '))
	{
		m_moveVector += m_transform.lock()->GetUp();
	}
	if(Input::GetKey('z'))
	{
		m_moveVector -= m_transform.lock()->GetUp();
	}

	if(m_moveVector != glm::vec3(0))
	{
		m_moveVector = glm::normalize(m_moveVector);
		m_transform.lock()->Translate(m_moveVector*m_speed*Time::GetDeltaTimeSec());
	}
}