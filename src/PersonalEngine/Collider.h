#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "glm/glm.hpp"

class Transform;
class RigidBody;

class Collider : public Component
{
public:
	virtual glm::vec3 GetMin();
	virtual glm::vec3 GetMax();
private:
	
	glm::vec3 m_center;
	glm::vec3 m_extents;

	std::weak_ptr<Transform> m_transform;
	std::weak_ptr<RigidBody> m_rigidBody;

	void Awake();
	void Destroy();

};



#endif