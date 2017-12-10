#ifndef _BULLETBEHAVIOUR_H_
#define _BULLETBEHAVIOUR_H_
#include "Component.h"

class BulletBehaviour : public Component
{
public:
	void ResetTimeAlive();
private:
	float m_timeAlive;

	void Awake();
	void Update();
};



#endif