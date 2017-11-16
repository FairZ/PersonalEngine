#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

class ResourceManager;

/// \brief Container and manager for everything needed per game level
class Scene
{
	friend class Entity;
	friend class Engine;
public:
	std::weak_ptr<ResourceManager> GetResourceManager();
	Scene();

private:
	std::vector<std::shared_ptr<Entity>> m_entities;

	std::shared_ptr<ResourceManager> m_resourceManager;

	bool LoadScene();
	void AddEntity(std::shared_ptr<Entity> _entity);

	void Awake();
	void Update();
	void Render();
};

#endif