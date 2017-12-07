#include "Light.h"
#include "Transform.h"
#include "Entity.h"
#include "RenderController.h"
#include "Scene.h"
#include "Camera.h"

void Light::Start()
{
	m_transform = m_entity->m_transform;
	m_entity->GetScene().lock()->GetRenderController().lock()->RegisterLight(m_entity->GetComponent<Light>());
}

void Light::Awake()
{
	m_type = 1;
	m_linearAtten = 0.09f;
	m_quadraticAtten = 0.032f;
	m_colour = glm::vec3(1,1,1);
}

glm::vec3 Light::GetPos()
{
	return m_transform.lock()->GetTransformationMatrix() * glm::vec4(0,0,0,1);
}

glm::vec3 Light::GetDir()
{
	return glm::mat3(m_transform.lock()->GetRotationMatrix()) * m_direction;
}

glm::vec3 Light::GetUp()
{
	return m_transform.lock()->GetUp();
}
