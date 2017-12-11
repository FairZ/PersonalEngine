#ifndef _TURNTABLE_H_
#define _TURNTABLE_H_
#include "Component.h"
#include <memory>

class Transform;

/// \brief Simple component which rotates the entity each frame
class TurnTable : public Component
{
public:

private:
	void Start();
	void Update();
	void SetReferences();
	std::weak_ptr<Transform> m_transform;
};


#endif