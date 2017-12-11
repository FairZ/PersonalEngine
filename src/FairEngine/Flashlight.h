#ifndef _FLAHSLIGHT_H_
#define _FLASHLIGHT_H_
#include "Component.h"

class Light;

/// \brief Allows toggling of a spotlight on and off
///
/// If a light is already attached to the entity it will be converted to a spot light otherwise a spot light will be added to the entity
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