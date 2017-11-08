#include "Scene.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Material.h"
#include "Engine.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "TurnTable.h"

Scene::Scene()
{
	m_resourceManager = std::make_shared<ResourceManager>();
}

std::weak_ptr<ResourceManager> Scene::GetResourceManager()
{
	std::weak_ptr<ResourceManager> retVal = m_resourceManager;
	return retVal;
}

bool Scene::LoadScene()
{
	//temporary scene setup (would normally handle loading)

	std::weak_ptr<Entity> cam = Entity::CreateEntity("Camera");
	std::weak_ptr<Entity> thing = Entity::CreateEntity("Thing");

	m_resourceManager->AddShader("ModelVertex.txt","ModelFragment.txt","Basic");
	m_resourceManager->AddMesh("teapot.obj","Log");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("Basic"),"BasicMat");

	std::weak_ptr<Camera> camComp = cam.lock()->AddComponent<Camera>();
	camComp.lock()->SetAsMainCamera();
	camComp.lock()->SetFOV(75.0f);
	camComp.lock()->SetNearClipPlane(0.1f);
	camComp.lock()->SetFarClipPlane(100.0f);
	cam.lock()->m_transform->Translate(glm::vec3(0,0,5));

	std::weak_ptr<MeshRenderer> meshrenderer = thing.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Log");
	meshrenderer.lock()->SetMaterial("BasicMat");
	thing.lock()->AddComponent<TurnTable>();
	thing.lock()->m_transform->Scale(glm::vec3(0.5f,0.5f,0.5f));

	Awake();
	return true;
}

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
	m_entities.push_back(_entity);
}

void Scene::Awake()
{
	for(auto i : m_entities)
	{
		i->Awake();
	}
}

void Scene::Update()
{
	for(auto i : m_entities)
	{
		i->Update();
	}
}

void Scene::Render()
{
	//set camera view and projection matricies in all materials before drawing to avoid repeated calls
	Camera::mainCamera.lock()->CalculateProjectionMatrix();
	Camera::mainCamera.lock()->CalculateViewMatrix();

	for (auto i : m_resourceManager->m_materials)
	{
		i->SetMat4("viewMat",Camera::mainCamera.lock()->GetViewMatrix());
		i->SetMat4("projMat",Camera::mainCamera.lock()->GetProjectionMatrix());
	}

	for(auto i : m_entities)
	{
		i->Render();
	}
}