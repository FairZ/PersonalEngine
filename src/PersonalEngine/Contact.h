#ifndef _CONTACT_H_
#define _CONTACT_H_
#include "glm/glm.hpp"
#include <memory>

class RigidBody;

class Contact
{
public:
	Contact(){}
	Contact(glm::vec3 _normal, glm::vec3 _position, float _penetration, std::weak_ptr<RigidBody> _body1, std::weak_ptr<RigidBody> _body2);
	void Resolve();
private:
	glm::vec3 m_normal;
	glm::vec3 m_position;
	float m_penetration;
	std::weak_ptr<RigidBody> m_body1;
	std::weak_ptr<RigidBody> m_body2;
};



#endif