#ifndef _BULLET_H_
#define _BULLET_H_
#include "Entity.h"

/// \brief Prefab used by Gun for firing
class Bullet : public Entity
{
public:
	void Initialise();
	void Reset();
private:
	std::weak_ptr<Entity> m_initialParent;
	glm::vec3 m_initialPosition;
	glm::vec3 m_initialRotation;
	glm::vec3 m_initialScale;
};

#endif