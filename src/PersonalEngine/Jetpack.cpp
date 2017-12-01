#include "Jetpack.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Input.h"

void Jetpack::Start()
{
	m_rb = m_entity->GetComponent<RigidBody>();
}

void Jetpack::FixedUpdate()
{
	if (Input::GetKey(' '))
	{
		if (!m_rb.expired())
		{
			m_rb.lock()->AddForce(glm::vec3(0, 20.0f, 0));
		}
	}
}
