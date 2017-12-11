#ifndef _JETPACK_H_
#define _JETPACK_H_
#include "Component.h"

class RigidBody;

/// \brief Pushes Entity upwards when space is pressed
class Jetpack : public Component
{
public:

private:
	std::weak_ptr<RigidBody> m_rb;

	void Start();
	void FixedUpdate();
	void SetReferences();
};



#endif