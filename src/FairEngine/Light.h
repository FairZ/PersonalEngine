#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Component.h"
#include "glm/glm.hpp"

class Transform;

/// \brief Stores all values of any light type and registers self with RenderController on startup
class Light : public Component
{
	friend class RenderController;
public:
	void SetType(int _type){m_type = _type;}
	void SetColour(glm::vec3 _colour){m_colour = _colour;}
	void SetDirection(glm::vec3 _direction){m_direction = _direction;}
	void SetInnerCutoff(float _inner){m_innerCutoff = _inner;}
	void SetOuterCutoff(float _outer){m_outerCutoff = _outer;}
	void SetLinearAtten(float _linear){m_linearAtten = _linear;}
	void SetQuadraticAtten(float _quadratic){m_quadraticAtten = _quadratic;}

private:
	void Start();
	void Awake();
	void SetReferences();
	glm::vec3 GetPos();
	glm::vec3 GetTranslatedPos();
	glm::vec3 GetDir();
	glm::vec3 GetLocalDir();
	glm::vec3 GetUp();

	std::weak_ptr<Transform> m_transform;

	int m_type;
	glm::vec3 m_colour;
	glm::vec3 m_direction;
	float m_innerCutoff;
	float m_outerCutoff;
	float m_linearAtten;
	float m_quadraticAtten;
};


#endif