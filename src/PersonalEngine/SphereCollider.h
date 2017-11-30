#ifndef _SPHERECOLLIDER_H_
#define _SPHERECOLLIDER_H_
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	void SetRadius(float _radius);

private:
	float m_radius;

	void Awake();
};


#endif