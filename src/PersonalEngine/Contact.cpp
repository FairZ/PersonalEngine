#include "Contact.h"
#include "RigidBody.h"

Contact::Contact(glm::vec3 _normal, glm::vec3 _position, float _penetration, std::weak_ptr<RigidBody> _body1, std::weak_ptr<RigidBody> _body2)
{
	m_normal = _normal;
	m_position = _position;
	m_penetration = _penetration;
	m_body1 = _body1;
	m_body2 = _body2;
}

void Contact::Resolve()
{
	glm::vec3 impulse;
	glm::vec3 v1;
	glm::vec3 v2;
	float invM1;
	float invM2;
	if (m_body1.expired())
	{
		v1 = glm::vec3(0);
		invM1 = 0;
	}
	else
	{
		v1 = m_body1.lock()->GetLinearVelocity();
		invM1 = 1 / m_body1.lock()->GetMass();
	}
	if (m_body2.expired())
	{
		v2 = glm::vec3(0);
		invM2 = 0;
	}
	else
	{
		v2 = m_body2.lock()->GetLinearVelocity();
		invM2 = 1 / m_body2.lock()->GetMass();
	}
	 

	impulse = (-1.9f * glm::cross(v1 - v2, m_normal)) / (invM1 + invM2);

	if (!m_body1.expired())
		m_body1.lock()->SetLinearVelocity((impulse*m_normal)*invM1);
	if (!m_body2.expired())
		m_body2.lock()->SetLinearVelocity((impulse*m_normal)*invM2);
}
