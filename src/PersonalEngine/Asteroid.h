#ifndef _ASTEROID_H_
#define _ASTEROID_H_
#include "Entity.h"

class Asteroid : public Entity
{
public:
	void Initialise();
	void Reset();
private:
	glm::vec3 m_initialPosition;
	glm::vec3 m_initialRotation;
	glm::vec3 m_initialScale;
};



#endif