#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Component.h"
#include <memory>
#include <glm/glm.hpp>


/// \brief Camera component, contains camera values used in the creation of a projection matrix
///
/// Instantiates a static reference to a Camera component which is used by the engine to render to the screen
class Camera : public Component
{
	friend class Engine;
public:
	static std::weak_ptr<Camera> mainCamera;
	
	void SetFOV(float _FOV);
	void SetOrthographic(bool _orthographic);
	void SetNearClipPlane(float _nearClipPlane);
	void SetFarClipPlane(float _farClipPlane);

	void SetAsMainCamera();
	void CalculateProjectionMatrix();
	void CalculateViewMatrix();
	glm::mat4 GetProjectionMatrix(){return m_projectionMatrix;}
	glm::mat4 GetViewMatrix(){return m_viewMatrix;}

private:
	float m_fieldOfView;
	bool m_orthographic;
	float m_nearClipPlane;
	float m_farClipPlane;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	
};


#endif