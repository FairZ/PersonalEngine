#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

class ResourceManager;
class CollisionResolver;

/// \brief Container and manager for everything needed per game level
class Scene
{
	friend class Entity;
	friend class Engine;
	friend class RenderController;
public:
	std::weak_ptr<ResourceManager> GetResourceManager();
	std::weak_ptr<CollisionResolver> GetCollisionResolver();
	std::weak_ptr<RenderController> GetRenderController();
	Scene();

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
	void Draw();
	void Resize();
};

#endif