#ifndef _COLLISIONRESOLVER_H_
#define _COLLISIONRESOLVER_H_
#include <memory>
#include <list>
#include <vector>

class RigidBody;
class Collider;
class Contact;

/// \brief Stores colliders flagged as potentially colliding during broad phase check
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


/// \brief Runs Broad and Narrow phase collision checks on colliders and runs contact resolutions
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