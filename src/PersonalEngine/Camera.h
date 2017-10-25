#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Component.h"
#include <memory>
#include <glm/glm.hpp>

class Camera : public Component
{
	friend class Engine;
public:
	static std::weak_ptr<Camera> mainCamera;
	
	void SetAsMainCamera();
	void CalculateProjectionMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

private:
	float m_fieldOFView;
	bool m_othographic;
	float m_nearClipPlane;
	float m_farClipPlane;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	
};


#endif