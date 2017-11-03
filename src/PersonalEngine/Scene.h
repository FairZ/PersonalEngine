#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>



class Scene
{
	friend class Entity;
	friend class Engine;
	friend class Resource;
public:

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Resource>> m_resources;

	bool LoadScene();
	void AddEntity(std::shared_ptr<Entity> _entity);
	void AddResource(std::shared_ptr<Resource> _resource);

	void Update();
	void Render();
};

#endif