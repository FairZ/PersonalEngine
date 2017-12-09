#include "Scene.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "RenderController.h"
#include "Camera.h"
#include "Material.h"
#include "Engine.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "TurnTable.h"
#include "Mesh.h"
#include "FlyingController.h"
#include "RigidBody.h"
#include "Jetpack.h"
#include "CollisionResolver.h"
#include "SphereCollider.h"
#include "Light.h"
#include "Flashlight.h"
#include "Gun.h"

void Scene::Init()
{
	Entity::m_scene = Engine::GetCurrentScene();
	m_resourceManager = std::make_shared<ResourceManager>();
	m_collisionResolver = std::make_shared<CollisionResolver>();
	m_renderController = std::make_shared<RenderController>();
}

std::weak_ptr<ResourceManager> Scene::GetResourceManager()
{
	std::weak_ptr<ResourceManager> retVal = m_resourceManager;
	return retVal;
}

std::weak_ptr<CollisionResolver> Scene::GetCollisionResolver()
{
	return m_collisionResolver;
}

std::weak_ptr<RenderController> Scene::GetRenderController()
{
	return m_renderController;
}

bool Scene::LoadScene()
{
	//temporary scene setup (would normally handle loading)

	
	std::weak_ptr<Entity> ship1 = Entity::CreateEntity("Ship1");
	std::weak_ptr<Entity> dirLight = Entity::CreateEntity("DirLight", "Ship1",glm::vec3(-2,0,0), glm::vec3(0), glm::vec3());
	std::weak_ptr<Entity> Grass = Entity::CreateEntity("Grass");
	std::weak_ptr<Entity> cam = Entity::CreateEntity("Camera","Ship1");
	std::weak_ptr<Entity> flashLight = Entity::CreateEntity("flashLight","Ship1",glm::vec3(0,0,1),glm::vec3(),glm::vec3(1.0f));

	m_resourceManager->AddShader("Shaders/ModelVertexNormal.txt","Shaders/ModelFragmentNormal.txt","Normal");
	m_resourceManager->AddShader("Shaders/ModelVertexNormal.txt","Shaders/ModelFragmentNormalSpecular.txt","NormalSpec");
	m_resourceManager->AddMesh("Models/Luminaris OBJ.obj","Ship", 0.05f);
	m_resourceManager->AddMesh("Models/Grass.obj","GrassMesh", 0.5f);
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"SpaceShip");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("Normal"),"Grass");
	m_resourceManager->AddTexture("Textures/Luminaris Diffuse.tga", "ShipDiffuse");
	m_resourceManager->AddTexture("Textures/Luminaris Normal.tga", "ShipNormal");
	m_resourceManager->AddTexture("Textures/Luminaris Specular.tga", "ShipSpec");
	m_resourceManager->AddTexture("Textures/Grass.png","GrassDiffuse");
	m_resourceManager->AddTexture("Textures/Grass_normal.png","GrassNormal");

	std::weak_ptr<Camera> camComp = cam.lock()->AddComponent<Camera>();
	camComp.lock()->SetAsMainCamera();
	camComp.lock()->SetFOV(75.0f);
	camComp.lock()->SetNearClipPlane(0.1f);
	camComp.lock()->SetFarClipPlane(100.0f);
	cam.lock()->m_transform->Translate(glm::vec3(0,1,-4));

	ship1.lock()->AddComponent<FlyingController>();

	std::weak_ptr<MeshRenderer> meshrenderer = ship1.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Ship");

	meshrenderer.lock()->SetMaterial(0,"SpaceShip");	
	std::weak_ptr<Material> mat = meshrenderer.lock()->GetMaterial(0);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("ShipDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("ShipNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("ShipSpec"));

	std::weak_ptr<Light> light = dirLight.lock()->AddComponent<Light>();
	light.lock()->SetDirection(glm::vec3(1.0f,0,0));
	light.lock()->SetType(2);
	light.lock()->SetColour(glm::vec3(0.5f,0.5f,0.5f));

	flashLight.lock()->AddComponent<Flashlight>();

	meshrenderer = Grass.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("GrassMesh");
	meshrenderer.lock()->SetMaterial(0,"Grass");
	mat = meshrenderer.lock()->GetMaterial(0);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("GrassDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("GrassNormal"));

	std::weak_ptr<Gun> gun = ship1.lock()->AddComponent<Gun>();

	m_renderController->Generate();

	Start();
	return true;
}

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
	int sameNameCount = 0;
	for(auto i : m_entities)
	{
		if (i->GetName() == _entity->GetName())
		{
			sameNameCount++;
		}
	}
	if (sameNameCount > 0)
		_entity->m_name = _entity->m_name + std::to_string(sameNameCount);
	m_entities.push_back(_entity);
}

void Scene::Destroy()
{
	//call the awake function in all entities
	for(auto i : m_entities)
	{
		i->Destroy();
	}
	m_entities.clear();
}

void Scene::Start()
{
	//call the awake function in all entities
	for(unsigned int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->Start();
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
		if(i->m_active)
		{
			i->Update();
		}
	}
}

void Scene::FixedUpdate()
{
	//run fixedUpdate function for all entities
	for (auto i : m_entities)
	{
		if(i->m_active)
		{
			i->FixedUpdate();
		}
	}
	m_collisionResolver->ResolveCollisions();
}

void Scene::Render()
{
	m_renderController->Render();
}

void Scene::ShadowPass()
{
	for(auto i : m_entities)
	{
		if(i->m_active)
		{
			i->ShadowRender();
		}
	}
}

void Scene::Draw()
{
	//run render function for all entities
	for(auto i : m_entities)
	{
		if(i->m_active)
		{
			i->Render();
		}
	}
}

void Scene::Resize()
{
	m_renderController->ResizeBuffer();
}