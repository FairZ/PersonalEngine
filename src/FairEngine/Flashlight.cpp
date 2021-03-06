#include "Flashlight.h"
#include "Light.h"
#include "Entity.h"
#include "Input.h"
#include "Scene.h"

void Flashlight::Awake()
{
	m_active = true;
}

void Flashlight::Start()
{
	SetReferences();
	m_spotlight.lock()->SetDirection(glm::vec3(0,0,1));
	m_spotlight.lock()->SetType(3);
	m_spotlight.lock()->SetColour(glm::vec3(1.0f,1.0f,1.0f));
	m_spotlight.lock()->SetInnerCutoff(glm::cos(glm::radians(12.5f)));
	m_spotlight.lock()->SetOuterCutoff(glm::cos(glm::radians(17.5f)));
}

void Flashlight::SetReferences()
{
	//set reference to light on the entity
	m_spotlight = m_entity->GetComponent<Light>();
	//if there is no light then add one
	if (m_spotlight.expired())
	{
		m_spotlight = m_entity->AddComponent<Light>();
	}
}

void Flashlight::Update()
{
	//turn the light on or off based on whether it is active
	if(m_active)
	{
		m_spotlight.lock()->SetColour(glm::vec3(1.0f,1.0f,1.0f));
	}
	else
	{
		m_spotlight.lock()->SetColour(glm::vec3());
	}
	//if the f key is pressed toggle the light
	if (Input::GetKeyDown('f'))
	{
		m_active = !m_active;
	}
}