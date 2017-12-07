#include "RenderController.h"
#include "Window.h"
#include "Shader.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <glm/gtc/matrix_transform.hpp>


RenderController::~RenderController()
{
	glDeleteVertexArrays(1, &m_QuadIndex);
	glDeleteRenderbuffers(1, &m_geomRenderBufferIndex);
	glDeleteTextures(1, &m_geomTextureBufferIndex);
	glDeleteFramebuffers(1, &m_geomFrameBufferIndex);
}

void RenderController::RegisterLight(std::weak_ptr<Light> _light)
{
	if(m_lightnum == 5)
	{
		m_lightnum = 0;
	}

	m_lights[m_lightnum] = _light;

	m_lightnum++;
}

void RenderController::Generate()
{
	m_resourceManager = Engine::m_currentScene->GetResourceManager();
	m_shadowMat = m_resourceManager.lock()->GetMaterial("ShadowMat");
	m_shadowRes = 2048;

	glGenFramebuffers(1, &m_shadowBufferIndex);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowBufferIndex);

	glGenTextures(1, & m_shadowTextureIndex);
	glBindTexture(GL_TEXTURE_2D, m_shadowTextureIndex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,m_shadowRes,m_shadowRes,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
	m_resourceManager.lock()->AddTexture(m_shadowTextureIndex, "ShadowTexture");
	m_shadowTex = m_resourceManager.lock()->GetTexture("ShadowTexture");

	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,m_shadowTextureIndex,0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glGenFramebuffers(1, &m_geomFrameBufferIndex);
	glBindFramebuffer(GL_FRAMEBUFFER, m_geomFrameBufferIndex);

	glGenTextures(1, &m_geomTextureBufferIndex);
	glBindTexture(GL_TEXTURE_2D, m_geomTextureBufferIndex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,Window::GetWidth(),Window::GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_geomTextureBufferIndex, 0);

	glGenRenderbuffers(1, &m_geomRenderBufferIndex);
	glBindRenderbuffer(GL_RENDERBUFFER,m_geomRenderBufferIndex);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,Window::GetWidth(),Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_geomRenderBufferIndex);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float quadVertexPositions[] = {  
    -1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f, -1.0f,

    -1.0f,  1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f
	};

	float quadVertexTexcoords[] = {
	0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_QuadIndex);
	glBindVertexArray(m_QuadIndex);

	GLuint positions;
	glGenBuffers(1, &positions);
	glBindBuffer(GL_ARRAY_BUFFER, positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, &quadVertexPositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	GLuint texcoords;
	glGenBuffers(1, &texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, &quadVertexTexcoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_postProcessShader = std::make_shared<Shader>("PPS","Shaders/PostProcessVertex.txt","Shaders/PostProcessFragment.txt");

}

void RenderController::ResizeBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_geomFrameBufferIndex);

	glBindTexture(GL_TEXTURE_2D, m_geomTextureBufferIndex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Window::GetWidth(),Window::GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);

	glBindRenderbuffer(GL_RENDERBUFFER,m_geomRenderBufferIndex);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,Window::GetWidth(),Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderController::ShadowPass()
{
	//set the lightmatrix of the shadow material (used for all models) to that of the directional light
	glm::mat4 lightMat;
	for (int l = 0; l < 5; l++)
	{
		if (!m_lights[l].expired())
		{
			if (m_lights[l].lock()->m_type == 2)
			{
				glm::mat4 lightProjection = glm::ortho(-5.0f,5.0f,-5.0f,5.0f,1.0f,10.0f);
				glm::mat4 lightView = glm::lookAt(m_lights[l].lock()->GetPos(), m_lights[l].lock()->GetPos() + m_lights[l].lock()->GetDir(), m_lights[l].lock()->GetUp());
				lightMat = lightProjection * lightView;
			}
		}
	}
	for (auto i: m_resourceManager.lock()->m_materials)
	{
		i->SetMat4("lightMat",lightMat);
	}
	glViewport(0,0,m_shadowRes,m_shadowRes);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowBufferIndex);
	glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_FRONT);
	Engine::m_currentScene->ShadowPass();
	glCullFace(GL_BACK);
}

void RenderController::GeomPass()
{
	//calculate and set camera view and projection matricies in all materials before drawing to avoid repeated calls
	Camera::mainCamera.lock()->CalculateProjectionMatrix();
	Camera::mainCamera.lock()->CalculateViewMatrix();

	for (auto i : m_resourceManager.lock()->m_materials)
	{
		i->SetMat4("viewMat",Camera::mainCamera.lock()->GetViewMatrix());
		i->SetMat4("projMat",Camera::mainCamera.lock()->GetProjectionMatrix());
		i->SetVec3("cameraPos", Camera::mainCamera.lock()->GetPos());
		i->SetTexture("ShadowMap",m_shadowTex);
		//for every light set the correct uniforms in all shaders
		int pointnum = 0;
		std::string light;
		for (int j = 0; j < 5; j++)
		{
			if(m_lights[j].expired())
			{
				light = "Lights["+std::to_string(pointnum)+"]";
				i->SetVec3(light+".position", glm::vec3());
				i->SetVec3(light+".colour", glm::vec3());
				i->SetFloat(light+".linear", 0.0f);
				i->SetFloat(light+".quadratic", 0.0f);
				pointnum++;
			}
			else
			{
				switch(m_lights[j].lock()->m_type)
				{
				case 1:
					light = "Lights["+std::to_string(pointnum)+"]";
					i->SetVec3(light+".position", m_lights[j].lock()->GetPos());
					i->SetVec3(light+".colour", m_lights[j].lock()->m_colour);
					i->SetFloat(light+".linear", m_lights[j].lock()->m_linearAtten);
					i->SetFloat(light+".quadratic", m_lights[j].lock()->m_quadraticAtten);
					pointnum++;
					break;
				case 2:
					i->SetVec3("DirectionalLight.direction", m_lights[j].lock()->GetDir());
					i->SetVec3("DirectionalLight.colour", m_lights[j].lock()->m_colour);
					break;
				case 3:
					i->SetVec3("SpotLight.colour", m_lights[j].lock()->m_colour);
					i->SetVec3("SpotLight.position", m_lights[j].lock()->GetPos());
					i->SetVec3("SpotLight.direction", m_lights[j].lock()->GetDir());
					i->SetFloat("SpotLight.linear", m_lights[j].lock()->m_linearAtten);
					i->SetFloat("SpotLight.quadratic", m_lights[j].lock()->m_quadraticAtten);
					i->SetFloat("SpotLight.inner", m_lights[j].lock()->m_innerCutoff);
					i->SetFloat("SpotLight.outer", m_lights[j].lock()->m_outerCutoff);		
					break;
				}
			}
		}
		//while the point light array is not full, fill it with empty lights
		while(pointnum < 5)
		{
			light = "Lights["+std::to_string(pointnum)+"]";
			i->SetVec3(light+".position", glm::vec3());
			i->SetVec3(light+".colour", glm::vec3());
			i->SetFloat(light+".linear", 0.0f);
			i->SetFloat(light+".quadratic", 0.0f);
			pointnum++;
		}
	}

	//bind the geometry buffer, clear it and draw all models to it
	glBindFramebuffer(GL_FRAMEBUFFER, m_geomFrameBufferIndex);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,Window::GetWidth(),Window::GetHeight());
	Engine::m_currentScene->Draw();
}

void RenderController::FinalPass()
{
	//bind the screen and clear it
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	//activate the postprocessing shader
	glUseProgram(m_postProcessShader->GetProgram());
	//bind the correct geometry texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_geomTextureBufferIndex);
	//bind the screen space quad
	glBindVertexArray(m_QuadIndex);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//draw to the screen space quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}

void RenderController::Render()
{
	ShadowPass();

	GeomPass();

	FinalPass();
}