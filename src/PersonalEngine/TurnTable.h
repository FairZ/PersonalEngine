#ifndef _TURNTABLE_H_
#define _TURNTABLE_H_
#include "Component.h"
#include <memory>

class Transform;

class TurnTable : public Component
{
public:

private:
	void Start();
	void Update();
	std::weak_ptr<Transform> m_transform;
};


#endif