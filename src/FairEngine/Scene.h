#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

class ResourceManager;
class CollisionResolver;

/// \brief Container and manager for everything needed per game level
///
/// Stored as a static reference in Engine, used to intialise ResourceManager, RenderController, CollisionResolver, and all resources and entities in a scene.
/// Holds all entities and runs a number of updates across all of them such as Update and Render
class Scene
{
	friend class Entity;
	friend class Engine;
	friend class RenderController;
public:
	std::weak_ptr<ResourceManager> GetResourceManager();
	std::weak_ptr<CollisionResolver> GetCollisionResolver();
	std::weak_ptr<RenderController> GetRenderController();

private:
	std::vector<std::shared_ptr<Entity>> m_entities;

	std::shared_ptr<ResourceManager> m_resourceManager;
	std::shared_ptr<CollisionResolver> m_collisionResolver;
	std::shared_ptr<RenderController> m_renderController;

	bool LoadScene();
	void AddEntity(std::shared_ptr<Entity> _entity);

	void Start();
	void Destroy();
	void Update();
	void FixedUpdate();
	void Render();
	void ShadowPass();
	void Draw();
	void Resize();

	void Init();
};

#endif