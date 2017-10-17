#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

class Scene
{
	friend class Entity;
	friend class Engine;
public:

private:
	std::vector<std::shared_ptr<Entity>> m_entities;

	bool LoadScene();
	void AddEntity(std::shared_ptr<Entity> _entity);

};

#endif