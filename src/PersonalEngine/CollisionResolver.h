#ifndef _COLLISIONRESOLVER_H_
#define _COLLISIONRESOLVER_H_
#include <memory>
#include <list>
#include <vector>

class RigidBody;
class Collider;
class Contact;

struct BroadCollision
{
	std::weak_ptr<Collider> m_collider1;
	std::weak_ptr<Collider> m_collider2;

	BroadCollision(std::weak_ptr<Collider> _1, std::weak_ptr<Collider> _2)
	{
		m_collider1 = _1;
		m_collider2 = _2;
	}
};

class CollisionResolver
{
	friend class Collider;
	friend class SphereCollider;
public:
	void ResolveCollisions();
private:
	void RegisterCollider(std::weak_ptr<Collider> _collider);
	void RemoveCollider(Collider* _collider);
	void BroadPhase();
	void NarrowPhase();
	void ResolveContacts();

	std::list<std::weak_ptr<Collider>> m_colliders;
	std::vector<BroadCollision> m_broadCollisions;
	std::vector<std::shared_ptr<Contact>> m_contacts;
};

#endif