#ifndef _FLAHSLIGHT_H_
#define _FLASHLIGHT_H_
#include "Component.h"

class Light;

class Flashlight : public Component
{
public:

private:

	void Awake();
	void Start();
	void Update();
	void SetReferences();

	bool m_active;
	std::weak_ptr<Light> m_spotlight;
};


#endif