#include "CollisionResolver.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Contact.h"
#include "SphereCollider.h"
#include "Entity.h"

void CollisionResolver::ResolveCollisions()
{
	//first run broad phase checks
	BroadPhase();

	//then runn narrow phase checks and clear then now unused broad collisions vector
	NarrowPhase();
	m_broadCollisions.clear();

	//resolve the contacts found by the narrow phase and clear them for the next loop
	ResolveContacts();
	m_contacts.clear();
}

void CollisionResolver::RegisterCollider(std::weak_ptr<Collider> _collider)
{
	m_colliders.push_back(_collider);
}

void CollisionResolver::RemoveCollider(Collider* _collider)
{
	for (auto i = m_colliders.begin(); i != m_colliders.end(); i++)
	{
		if ((*i).lock().get() == _collider)
		{
			m_colliders.erase(i);
			break;
		}
	}
}

void CollisionResolver::BroadPhase()
{
	//for every collider
	for (auto i = m_colliders.begin(); i != m_colliders.end(); i++)
	{
		//if they are active
		if (i->lock()->m_entity->GetActive())
		{
			//get the max and min values
			glm::vec3 iMax = (*i).lock()->GetMax();
			glm::vec3 iMin = (*i).lock()->GetMin();
			//then for every collider
			for (auto j = i; j != m_colliders.end(); j++)
			{
				//if they are active
				if (j->lock()->m_entity->GetActive())
				{
					//and not the first collider
					if (j != i)
					{
						//get the max and min values
						glm::vec3 jMax = (*j).lock()->GetMax();
						glm::vec3 jMin = (*j).lock()->GetMin();

						//do an AABB check to see if there may be a collision
						if (!(iMax.x < jMin.x || iMin.x > jMax.x ||
							iMax.y < jMin.y || iMin.y > jMax.y ||
							iMax.z < jMin.z || iMin.z > jMax.z))
						{
							//if there is push a register of the colliders to the broad collisions vector
							m_broadCollisions.push_back(BroadCollision((*i), (*j)));
						}
					}
				}
			}
		}
	}
}

void CollisionResolver::NarrowPhase()
{
	//for every collision found during broad phase
	for (auto i : m_broadCollisions)
	{
		//if it is a sphere-sphere collision
		if (i.m_collider1.lock()->GetType() == 's' && i.m_collider2.lock()->GetType() == 's')
		{
			//find the vector from one collider to the other
			glm::vec3 midline = i.m_collider1.lock()->GetWorldSpaceCenter() - i.m_collider2.lock()->GetWorldSpaceCenter();
			float distance = glm::length(midline);
			//if the distance of that line is smaller than their radii
			if (distance >= 0.0f && distance <= i.m_collider1.lock()->GetExtents().x + i.m_collider2.lock()->GetExtents().x)
			{
				//calculate other necessary values for collision resolution
				glm::vec3 normal = glm::normalize(midline);
				glm::vec3 position = i.m_collider1.lock()->GetWorldSpaceCenter() + midline * 0.5f;
				float penetration = i.m_collider1.lock()->GetExtents().x + i.m_collider2.lock()->GetExtents().x - distance;
				//and generate a new contact using those values
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
