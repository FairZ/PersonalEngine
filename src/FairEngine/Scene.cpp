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
#include "Asteroid.h"
#include "AudioSource.h"
#include <random>

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
	std::default_random_engine randGen;
	
	std::weak_ptr<Entity> ship1 = Entity::CreateEntity("Ship1");
	std::weak_ptr<Entity> dirLight = Entity::CreateEntity("DirLight", "Ship1",glm::vec3(-10,0,0), glm::vec3(0), glm::vec3());
	std::weak_ptr<Entity> cam = Entity::CreateEntity("Camera","Ship1");
	std::weak_ptr<Entity> flashLight = Entity::CreateEntity("flashLight","Ship1",glm::vec3(0,0,1),glm::vec3(),glm::vec3(1.0f));

	m_resourceManager->AddShader("Shaders/ModelVertexNormal.txt","Shaders/ModelFragmentNormalSpecularEmissive.txt","NormalSpecEmis");
	m_resourceManager->AddShader("Shaders/ModelVertexNormal.txt","Shaders/ModelFragmentNormalSpecular.txt","NormalSpec");
	m_resourceManager->AddMesh("Models/Luminaris OBJ.obj","Ship", 0.05f);
	m_resourceManager->AddMesh("Models/Meteor.obj","MeteorMesh", 1.0f);
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpecEmis"),"SpaceShip");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpecEmis"),"Bullet");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"Asteroid");
	m_resourceManager->AddTexture("Textures/Luminaris Diffuse.tga", "ShipDiffuse");
	m_resourceManager->AddTexture("Textures/Luminaris Normal.tga", "ShipNormal");
	m_resourceManager->AddTexture("Textures/Luminaris Specular.tga", "ShipSpec");
	m_resourceManager->AddTexture("Textures/Luminaris Emissive.tga", "ShipEmis");
	m_resourceManager->AddTexture("Textures/Meteor_d.tga","AsteroidDiffuse");
	m_resourceManager->AddTexture("Textures/Meteor_n.tga","AsteroidNormal");
	m_resourceManager->AddTexture("Textures/Meteor_s.tga","AsteroidSpec");
	m_resourceManager->AddSound("Sounds/Shoot.ogg","Shoot");
	m_resourceManager->AddSound("Sounds/OutThere.ogg","Music");

	m_resourceManager->GetMaterial("Asteroid").lock()->SetTexture("colourTexture", m_resourceManager->GetTexture("AsteroidDiffuse"));
	m_resourceManager->GetMaterial("Asteroid").lock()->SetTexture("normalTexture", m_resourceManager->GetTexture("AsteroidNormal"));
	m_resourceManager->GetMaterial("Asteroid").lock()->SetTexture("specularTexture", m_resourceManager->GetTexture("AsteroidSpec"));

	m_resourceManager->GetMaterial("Bullet").lock()->SetTexture("colourTexture", m_resourceManager->GetTexture("ShipDiffuse"));
	m_resourceManager->GetMaterial("Bullet").lock()->SetTexture("normalTexture", m_resourceManager->GetTexture("ShipNormal"));
	m_resourceManager->GetMaterial("Bullet").lock()->SetTexture("specularTexture", m_resourceManager->GetTexture("ShipSpec"));
	m_resourceManager->GetMaterial("Bullet").lock()->SetTexture("emissiveTexture", m_resourceManager->GetTexture("ShipDiffuse"));


	std::weak_ptr<Camera> camComp = cam.lock()->AddComponent<Camera>();
	camComp.lock()->SetAsMainCamera();
	camComp.lock()->SetFOV(75.0f);
	camComp.lock()->SetNearClipPlane(0.1f);
	camComp.lock()->SetFarClipPlane(1000.0f);
	cam.lock()->m_transform->Translate(glm::vec3(0,1,-4));

	std::weak_ptr<AudioSource> audio = cam.lock()->AddComponent<AudioSource>();
	audio.lock()->SetSound("Music");
	audio.lock()->SetLooping(true);
	audio.lock()->SetGain(0.7f);
	audio.lock()->Play();

	audio = ship1.lock()->AddComponent<AudioSource>();
	audio.lock()->SetSound("Shoot");
	audio.lock()->SetGain(1.5f);

	std::weak_ptr<RigidBody> rb = ship1.lock()->AddComponent<RigidBody>();
	rb.lock()->SetGravity(glm::vec3());
	rb.lock()->SetDrag(0.5f);
	std::weak_ptr<SphereCollider> sphere = ship1.lock()->AddComponent<SphereCollider>();
	sphere.lock()->SetRadius(0.5f);
	ship1.lock()->AddComponent<FlyingController>();

	std::weak_ptr<MeshRenderer> meshrenderer = ship1.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Ship");

	meshrenderer.lock()->SetMaterial(0,"SpaceShip");	
	std::weak_ptr<Material> mat = meshrenderer.lock()->GetMaterial(0);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("ShipDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("ShipNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("ShipSpec"));
	mat.lock()->SetTexture("emissiveTexture",m_resourceManager->GetTexture("ShipEmis"));

	std::weak_ptr<Light> light = dirLight.lock()->AddComponent<Light>();
	light.lock()->SetDirection(glm::vec3(1.0f,0,0));
	light.lock()->SetType(2);
	light.lock()->SetColour(glm::vec3(0.2f,0.09f,0.05f));

	flashLight.lock()->AddComponent<Flashlight>();

	std::weak_ptr<Gun> gun = ship1.lock()->AddComponent<Gun>();

	std::uniform_real_distribution<float> posX(-100.0f, 100.0f);
	std::uniform_real_distribution<float> posY(-100.0f, 100.0f);
	std::uniform_real_distribution<float> posZ(-100.0f, 100.0f);
	std::uniform_real_distribution<float> rotX(glm::radians(-180.0f), glm::radians(180.0f));
	std::uniform_real_distribution<float> rotY(glm::radians(-180.0f), glm::radians(180.0f));
	std::uniform_real_distribution<float> rotZ(glm::radians(-180.0f), glm::radians(180.0f));
	std::uniform_real_distribution<float> scale(0.5f,1.5f);

	int astNum = 0;
	for (astNum; astNum < 50; astNum++)
	{
		float scaler = scale(randGen);
		Entity::InstantiatePrefab<Asteroid>("Ast" + std::to_string(astNum) , glm::vec3(posX(randGen), posY(randGen), posZ(randGen)), glm::vec3(rotX(randGen), rotY(randGen),rotZ(randGen)), glm::vec3(scaler));
	}

	m_renderController->Generate();

	Start();
	return true;
}

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
	//when adding an entity if it has the same name as an already existing entity increment its name so that no two entities have the same name
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
	//call the destroy function in all entities
	for(auto i : m_entities)
	{
		i->Destroy();
	}
	m_entities.clear();
}

void Scene::Start()
{
	//call the start function in all entities
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
	//run shadowrender function for all entities
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