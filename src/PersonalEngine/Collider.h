#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "glm/glm.hpp"

class Transform;
class RigidBody;

class Collider : public Component
{
	friend class CollisionResolver;
public:
	glm::vec3 GetMin();
	glm::vec3 GetMax();
	glm::vec3 GetExtents();
	char GetType();
	glm::vec3 GetWorldSpaceCenter();
	std::weak_ptr<RigidBody> GetRigidBody();

	void SetCenter(glm::vec3 _center);

protected:
	glm::vec3 m_center;
	glm::vec3 m_extents;
	char m_type;

	std::weak_ptr<Transform> m_transform;
	std::weak_ptr<RigidBody> m_rigidBody;

	virtual void Start();
	void Destroy();

};



#endif