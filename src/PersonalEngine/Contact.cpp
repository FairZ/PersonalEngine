#include "Contact.h"
#include "RigidBody.h"
#include "Time.h"
#include "Transform.h"

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
	float impulse;
	glm::vec3 v1;
	glm::vec3 v2;
	float invM1 = 0.0f;
	float invM2 = 0.0f;
	float posCorrect1 = 0.0f;
	float posCorrect2 = 0.0f;
	glm::vec3 scaledNormal = m_normal * Time::GetFixedDeltaTimeSec();
	float velocityFromAcceleration = 0;

	if (!m_body1.expired())
	{
		v1 = m_body1.lock()->GetLinearVelocity();
		invM1 = 1 / m_body1.lock()->GetMass();
		velocityFromAcceleration += glm::dot(m_body1.lock()->GetLinearAcceleration(), scaledNormal);
		posCorrect1 = m_penetration*invM1;
		m_body1.lock()->GetTransform().lock()->Translate(m_normal*posCorrect1);
	}

	if (!m_body2.expired())
	{
		v2 = m_body2.lock()->GetLinearVelocity();
		invM2 = 1 / m_body2.lock()->GetMass();
		velocityFromAcceleration -= glm::dot(m_body2.lock()->GetLinearAcceleration(), scaledNormal);
		posCorrect2 = -m_penetration*invM2;
		m_body2.lock()->GetTransform().lock()->Translate(m_normal*posCorrect2);
	}

	float restitution = -0.9f;
	float contactVelocity = glm::dot(v1 - v2, m_normal) - velocityFromAcceleration;
	if (contactVelocity > -0.2f)
		restitution = 0.0f;

	impulse = (restitution * contactVelocity) / (invM1 + invM2);

	if (!m_body1.expired())
		m_body1.lock()->SetLinearVelocity((impulse*m_normal)*invM1);
	if (!m_body2.expired())
		m_body2.lock()->SetLinearVelocity((-impulse*m_normal)*invM2);
}
