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
	glDeleteVertexArrays(1, &m_boxIndex);
	glDeleteVertexArrays(1, &m_QuadIndex);
	glDeleteRenderbuffers(1, &m_geomRenderBufferIndex);
	glDeleteTextures(1, &m_geomTextureBufferIndex);
	glDeleteTextures(1, &m_shadowTextureIndex);
	glDeleteTextures(1, &m_finalTextureBufferIndex);
	glDeleteFramebuffers(1, &m_geomFrameBufferIndex);
	glDeleteFramebuffers(1, &m_shadowBufferIndex);
	glDeleteFramebuffers(1, &m_finalFrameBufferIndex);
}

void RenderController::RegisterLight(std::weak_ptr<Light> _light)
{
	//register up to 5 lights in the scene
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

#pragma region Skybox setup
	std::string paths[] = {"Textures/SpaceMap/leftImage.png", "Textures/SpaceMap/rightImage.png", "Textures/SpaceMap/upImage.png", "Textures/SpaceMap/downImage.png", "Textures/SpaceMap/frontImage.png", "Textures/SpaceMap/backImage.png"};
	//load the skybox texture and setup a material with said texture
	m_resourceManager.lock()->AddCubeMap(paths, "Skybox");
	m_skybox = m_resourceManager.lock()->GetCubeMap("Skybox");
	m_resourceManager.lock()->AddShader("Shaders/SkyboxVertex.txt", "Shaders/SkyboxFragment.txt", "Skybox");
	m_resourceManager.lock()->AddMaterial(m_resourceManager.lock()->GetShader("Skybox"), "SkyboxMat");
	m_skyboxMat = m_resourceManager.lock()->GetMaterial("SkyboxMat");
	m_skyboxMat.lock()->SetCubeMap("skybox", m_skybox);

	//hardcoded inward facing box
	float boxVertexPositions[] = {

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	//generate a VAO for the box
	glGenVertexArrays(1, &m_boxIndex);
	glBindVertexArray(m_boxIndex);

	GLuint pos;
	glGenBuffers(1, &pos);
	glBindBuffer(GL_ARRAY_BUFFER,pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, &boxVertexPositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

#pragma endregion
#pragma region Shadow Setup

	//get the shadow material
	m_shadowMat = m_resourceManager.lock()->GetMaterial("ShadowMat");
	m_shadowRes = 2048;

	//generate teh shadow's framebuffer
	glGenFramebuffers(1, &m_shadowBufferIndex);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowBufferIndex);

	//generate a depth texture
	glGenTextures(1, & m_shadowTextureIndex);
	glBindTexture(GL_TEXTURE_2D, m_shadowTextureIndex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,m_shadowRes,m_shadowRes,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 
	//add this texture to the resource manager
	m_resourceManager.lock()->AddTexture(m_shadowTextureIndex, "ShadowTexture");
	m_shadowTex = m_resourceManager.lock()->GetTexture("ShadowTexture");

	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,m_shadowTextureIndex,0);
	//set it to only draw the depth buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

#pragma endregion
#pragma region Geometry pass setup

	//generate a framebuffer for rendering the geometry with multismapled textures for MSAA
	glGenFramebuffers(1, &m_geomFrameBufferIndex);
	glBindFramebuffer(GL_FRAMEBUFFER, m_geomFrameBufferIndex);

	glGenTextures(1, &m_geomTextureBufferIndex);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_geomTextureBufferIndex);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,6,GL_RGB32F,Window::GetWidth(),Window::GetHeight(),GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_geomTextureBufferIndex, 0);
	
	glGenRenderbuffers(1, &m_geomRenderBufferIndex);
	glBindRenderbuffer(GL_RENDERBUFFER,m_geomRenderBufferIndex);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 6, GL_DEPTH24_STENCIL8, Window::GetWidth(), Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_geomRenderBufferIndex);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#pragma endregion
#pragma region PostProccess Setup

	///generate the final framebuffer
	glGenFramebuffers(1, &m_finalFrameBufferIndex);
	glBindFramebuffer(GL_FRAMEBUFFER, m_finalFrameBufferIndex);

	glGenTextures(1, &m_finalTextureBufferIndex);
	glBindTexture(GL_TEXTURE_2D, m_finalTextureBufferIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Window::GetWidth(), Window::GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_finalTextureBufferIndex, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//hard coded screen quad
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

	//generate a VAO for the screen quad
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

	//create a post process shader
	m_postProcessShader = std::make_shared<Shader>("PPS","Shaders/PostProcessVertex.txt","Shaders/PostProcessFragment.txt");

#pragma endregion

}

void RenderController::ResizeBuffer()
{
	//resize all textures and renderbuffers to fit the new screen size
	glBindFramebuffer(GL_FRAMEBUFFER, m_geomFrameBufferIndex);
	
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_geomTextureBufferIndex);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 6, GL_RGB32F, Window::GetWidth(), Window::GetHeight(), GL_TRUE);
	
	glBindRenderbuffer(GL_RENDERBUFFER,m_geomRenderBufferIndex);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 6, GL_DEPTH24_STENCIL8,Window::GetWidth(),Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_finalFrameBufferIndex);

	glBindTexture(GL_TEXTURE_2D, m_finalTextureBufferIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Window::GetWidth(), Window::GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

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
				glm::mat4 lightProjection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,1.0f,50.0f);
				glm::mat4 lightView = glm::lookAt(m_lights[l].lock()->GetTranslatedPos(), m_lights[l].lock()->GetTranslatedPos() + m_lights[l].lock()->GetLocalDir(), m_lights[l].lock()->GetUp());
				lightMat = lightProjection * lightView;
			}
		}
	}
	for (auto i: m_resourceManager.lock()->m_materials)
	{
		i->SetMat4("lightMat",lightMat);
	}
	//set the correct viewport
	glViewport(0,0,m_shadowRes,m_shadowRes);
	//bind the shadow framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowBufferIndex);
	glClear(GL_DEPTH_BUFFER_BIT);
	//disable cullface to avoid peter-panning
	glDisable(GL_CULL_FACE);
	//draw all objects using the shadow material
	Engine::m_currentScene->ShadowPass();
	glEnable(GL_CULL_FACE);
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
					i->SetVec3("DirectionalLight.direction", m_lights[j].lock()->GetLocalDir());
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
	//draw the skybox last with its depth value maxed to avoid drawing unnecessary pixels
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(m_boxIndex);
	glEnableVertexAttribArray(0);
	m_skyboxMat.lock()->ReadyForDraw();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void RenderController::PostProcessPass()
{
	//blit from the geometry buffer to teh final buffer to downsample to 1 sample per pixel
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_geomFrameBufferIndex);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_finalFrameBufferIndex);
	glBlitFramebuffer(0, 0, Window::GetWidth(), Window::GetHeight(), 0, 0, Window::GetWidth(), Window::GetHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);

	//bind the screen and clear it
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	//activate the postprocessing shader
	glUseProgram(m_postProcessShader->GetProgram());
	//bind the correct geometry texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_finalTextureBufferIndex);
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
	//first run the shadow pass
	ShadowPass();
	//then render the geometry
	GeomPass();
	//then render the final screen quad
	PostProcessPass();
}