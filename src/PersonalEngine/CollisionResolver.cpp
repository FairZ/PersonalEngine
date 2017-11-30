#include "CollisionResolver.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Contact.h"
#include "SphereCollider.h"

void CollisionResolver::ResolveCollisions()
{
	BroadPhase();

	NarrowPhase();
	m_broadCollisions.clear();

	ResolveContacts();
	m_contacts.clear();
}

void CollisionResolver::RegisterCollider(std::weak_ptr<Collider> _collider)
{
	m_colliders.push_back(_collider);
}

void CollisionResolver::RemoveCollider(std::weak_ptr<Collider> _collider)
{
	for (auto i = m_colliders.begin(); i != m_colliders.end(); i++)
	{
		if ((*i).lock().get() == _collider.lock().get())
		{
			m_colliders.erase(i);
			break;
		}
	}
}

void CollisionResolver::BroadPhase()
{
	for (auto i = m_colliders.begin(); i != m_colliders.end(); i++)
	{
		glm::vec3 iMax = (*i).lock()->GetMax();
		glm::vec3 iMin = (*i).lock()->GetMin();
		for (auto j = i; j != m_colliders.end(); j++)
		{
			if (j != i)
			{
				glm::vec3 jMax = (*j).lock()->GetMax();
				glm::vec3 jMin = (*j).lock()->GetMin();

				if (!(iMax.x < jMin.x || iMin.x > jMax.x ||
					iMax.y < jMin.y || iMin.y > jMax.y ||
					iMax.z < jMin.z || iMin.z > jMax.z))
				{
					m_broadCollisions.push_back(BroadCollision((*i), (*j)));
				}
			}
		}
	}
}

void CollisionResolver::NarrowPhase()
{
	for (auto i : m_broadCollisions)
	{
		//ADD ABILITY TO DO OTHER TYPES OF COLLISION CHECK
		if (i.m_collider1.lock()->GetType() == 's' && i.m_collider2.lock()->GetType() == 's')
		{
			glm::vec3 midline = i.m_collider1.lock()->GetWorldSpaceCenter() - i.m_collider2.lock()->GetWorldSpaceCenter();
			float distance = midline.length();
			if (distance >= 0.0f && distance <= i.m_collider1.lock()->GetExtents().x + i.m_collider2.lock()->GetExtents().x)
			{
				glm::vec3 normal = glm::normalize(midline);
				glm::vec3 position = i.m_collider1.lock()->GetWorldSpaceCenter() + midline * 0.5f;
				float penetration = i.m_collider1.lock()->GetExtents().x + i.m_collider2.lock()->GetExtents().x - distance;
				m_contacts.push_back(std::make_shared<Contact>(normal, position, penetration, i.m_collider1.lock()->GetRigidBody(), i.m_collider2.lock()->GetRigidBody()));
			}
		}
	}
}

void CollisionResolver::ResolveContacts()
{
	for (auto i : m_contacts)
	{
		i->Resolve();
	}
}
