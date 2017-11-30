#include "Scene.h"
#include "Entity.h"
#include "ResourceManager.h"
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

Scene::Scene()
{
	m_resourceManager = std::make_shared<ResourceManager>();
	m_collisionResolver = std::make_shared<CollisionResolver>();
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

bool Scene::LoadScene()
{
	//temporary scene setup (would normally handle loading)

	std::weak_ptr<Entity> cam = Entity::CreateEntity("Camera");
	std::weak_ptr<Entity> thing3 = Entity::CreateEntity("LightMesh",glm::vec3(0,2,0), glm::vec3(0), glm::vec3(0.1f,0.1f,0.1f));
	std::weak_ptr<Entity> thing = Entity::CreateEntity("Thing");
	std::weak_ptr<Entity> thing2 = Entity::CreateEntity("Thing2");

	m_resourceManager->AddShader("Shaders/ModelVertexNormal.txt","Shaders/ModelFragmentNormal.txt","Normal");
	m_resourceManager->AddShader("Shaders/ModelVertexNormal.txt","Shaders/ModelFragmentNormalSpecular.txt","NormalSpec");
	m_resourceManager->AddMesh("Models/nanosuit.obj","Suit", 0.06f);
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("Normal"),"Glass");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"Leg");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"Hand");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"Arm");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"Helmet");
	m_resourceManager->AddMaterial(m_resourceManager->GetShader("NormalSpec"),"Body");
	m_resourceManager->AddTexture("Textures/glass_dif.png","GlassDiffuse");
	m_resourceManager->AddTexture("Textures/glass_ddn.png","GlassNormal");
	m_resourceManager->AddTexture("Textures/leg_dif.png","LegDiffuse");
	m_resourceManager->AddTexture("Textures/leg_ddn.png","LegNormal");
	m_resourceManager->AddTexture("Textures/leg_spec.png","LegSpec");
	m_resourceManager->AddTexture("Textures/hand_dif.png","HandDiffuse");
	m_resourceManager->AddTexture("Textures/hand_ddn.png","HandNormal");
	m_resourceManager->AddTexture("Textures/hand_spec.png","HandSpec");
	m_resourceManager->AddTexture("Textures/arm_dif.png","ArmDiffuse");
	m_resourceManager->AddTexture("Textures/arm_ddn.png","ArmNormal");
	m_resourceManager->AddTexture("Textures/arm_spec.png","ArmSpec");
	m_resourceManager->AddTexture("Textures/helmet_dif.png","HelmetDiffuse");
	m_resourceManager->AddTexture("Textures/helmet_ddn.png","HelmetNormal");
	m_resourceManager->AddTexture("Textures/helmet_spec.png","HelmetSpec");
	m_resourceManager->AddTexture("Textures/body_dif.png","BodyDiffuse");
	m_resourceManager->AddTexture("Textures/body_ddn.png","BodyNormal");
	m_resourceManager->AddTexture("Textures/body_spec.png","BodySpec");

	std::weak_ptr<Camera> camComp = cam.lock()->AddComponent<Camera>();
	camComp.lock()->SetAsMainCamera();
	camComp.lock()->SetFOV(75.0f);
	camComp.lock()->SetNearClipPlane(0.1f);
	camComp.lock()->SetFarClipPlane(100.0f);
	cam.lock()->m_transform->Translate(glm::vec3(0,1,3));

	//cam.lock()->AddComponent<FlyingController>();

	thing.lock()->m_transform->Translate(glm::vec3(0,0,-2));
	thing.lock()->AddComponent<RigidBody>().lock()->SetGravity(glm::vec3(0));
	thing.lock()->AddComponent<SphereCollider>();
	thing.lock()->AddComponent<Jetpack>();

	thing2.lock()->m_transform->Translate(glm::vec3(0, 2, -2));
	thing2.lock()->AddComponent<RigidBody>().lock()->SetGravity(glm::vec3(0));
	thing2.lock()->AddComponent<SphereCollider>();

	std::weak_ptr<MeshRenderer> meshrenderer = thing.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Suit");

	meshrenderer.lock()->SetMaterial(0,"Glass");	
	std::weak_ptr<Material> mat = meshrenderer.lock()->GetMaterial(0);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("GlassDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("GlassNormal"));

	meshrenderer.lock()->SetMaterial(1,"Leg");	
	mat = meshrenderer.lock()->GetMaterial(1);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("LegDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("LegNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("LegSpec"));

	meshrenderer.lock()->SetMaterial(2,"Hand");	
	mat = meshrenderer.lock()->GetMaterial(2);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("HandDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("HandNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("HandSpec"));

	meshrenderer.lock()->SetMaterial(3,"Glass");	
	
	meshrenderer.lock()->SetMaterial(4,"Arm");	
	mat = meshrenderer.lock()->GetMaterial(4);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("ArmDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("ArmNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("ArmSpec"));

	meshrenderer.lock()->SetMaterial(5,"Helmet");	
	mat = meshrenderer.lock()->GetMaterial(5);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("HelmetDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("HelmetNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("HelmetSpec"));

	meshrenderer.lock()->SetMaterial(6,"Body");	
	mat = meshrenderer.lock()->GetMaterial(6);
	mat.lock()->SetTexture("colourTexture",m_resourceManager->GetTexture("BodyDiffuse"));
	mat.lock()->SetTexture("normalTexture",m_resourceManager->GetTexture("BodyNormal"));
	mat.lock()->SetTexture("specularTexture",m_resourceManager->GetTexture("BodySpec"));

	thing2.lock()->AddComponent<TurnTable>();

	meshrenderer = thing2.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Suit");
	meshrenderer.lock()->SetMaterial(0,"Glass");
	meshrenderer.lock()->SetMaterial(1,"Leg");	
	meshrenderer.lock()->SetMaterial(2,"Hand");	
	meshrenderer.lock()->SetMaterial(3,"Glass");
	meshrenderer.lock()->SetMaterial(4,"Arm");	
	meshrenderer.lock()->SetMaterial(5,"Helmet");	
	meshrenderer.lock()->SetMaterial(6,"Body");

	meshrenderer = thing3.lock()->AddComponent<MeshRenderer>();
	meshrenderer.lock()->SetMesh("Suit");
	meshrenderer.lock()->SetMaterial(0,"Glass");
	meshrenderer.lock()->SetMaterial(1,"Leg");	
	meshrenderer.lock()->SetMaterial(2,"Hand");	
	meshrenderer.lock()->SetMaterial(3,"Glass");
	meshrenderer.lock()->SetMaterial(4,"Arm");	
	meshrenderer.lock()->SetMaterial(5,"Helmet");	
	meshrenderer.lock()->SetMaterial(6,"Body");

	Awake();
	return true;
}

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
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

void Scene::FixedUpdate()
{
	//run fixedUpdate function for all entities
	for (auto i : m_entities)
	{
		i->FixedUpdate();
	}
	m_collisionResolver->ResolveCollisions();
}

void Scene::Render()
{
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