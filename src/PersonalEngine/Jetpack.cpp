#include "Jetpack.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Input.h"

void Jetpack::Awake()
{
	m_rb = m_entity->GetComponent<RigidBody>();
}

void Jetpack::Update()
{
	if (Input::GetKey(' '))
	{
		m_rb.lock()->AddForce(glm::vec3(0, 20.0f, 0));
	}
}
