#include "Resource.h"

std::weak_ptr<Resource> Resource::FindResource(std::string _name)
{
	weak_ptr<Entity> retval;

	for(auto i : m_scene.lock()->m_entities)
	{
		if (i->m_name == _name)
		{
			retval = i;
			break;
		}
	}

	return retval;
}