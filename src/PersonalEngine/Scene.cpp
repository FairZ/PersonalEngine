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
	std::weak_ptr<Entity> thing2 = Entity::CreateEntity("Thing2","Thing",glm::vec3(0.0f,1.0f,2.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1,1,1));

	m_resourceManager->AddShader("ModelVertex.txt","ModelFragment.txt","Basic");
	m_resourceManager->AddMesh("Log_pine.obj","Log", 0.03f);
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("Basic"),"BasicMat");
	m_resourceManager->AddTexture("Log_pine_color.png","texture");
	m_resourceManager->AddTexture("Log_pin_normal.png", "normal");

	std::weak_ptr<Camera> camComp = cam.lock()->AddComponent<Camera>();
	camComp.lock()->SetAsMainCamera();
	camComp.lock()->SetFOV(75.0f);
	camComp.lock()->SetNearClipPlane(0.1f);
	camComp.lock()->SetFarClipPlane(100.0f);
	cam.lock()->m_transform->Translate(glm::vec3(0,0,5));

	std::weak_ptr<MeshRenderer> meshrenderer = thing.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Log");
	meshrenderer.lock()->SetMaterial("BasicMat");
	std::weak_ptr<Material> mat = meshrenderer.lock()->GetMaterial();
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("texture"));
	mat.lock()->SetTexture("normalTexture", m_resourceManager->GetTexture("normal"));
	thing.lock()->AddComponent<TurnTable>();

	meshrenderer = thing2.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Log");
	meshrenderer.lock()->SetMaterial("BasicMat");
	mat = meshrenderer.lock()->GetMaterial();
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("texture"));

	Awake();
	return true;
}

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
	m_entities.push_back(_entity);
}

void Scene::Awake()
{
	//call the awake function in all entities
	for(auto i : m_entities)
	{
		i->Awake();
	}
}

void Scene::Update()
{
	//sweep and destroy any dead entities
	for(unsigned int i = 0; i < m_entities.size() ; i++)
	{
		if(m_entities[i]->m_destroyed)
		{
			m_entities.erase(m_entities.begin()+i);
			i--;
		}
	}
	//run update function for all entities
	for(auto i : m_entities)
	{
		i->Update();
	}
}

void Scene::Render()
{
	//calculate and set camera view and projection matricies in all materials before drawing to avoid repeated calls
	Camera::mainCamera.lock()->CalculateProjectionMatrix();
	Camera::mainCamera.lock()->CalculateViewMatrix();
	for (auto i : m_resourceManager->m_materials)
	{
		i->SetMat4("viewMat",Camera::mainCamera.lock()->GetViewMatrix());
		i->SetMat4("projMat",Camera::mainCamera.lock()->GetProjectionMatrix());
	}

	//run render function for all entities
	for(auto i : m_entities)
	{
		i->Render();
	}
}