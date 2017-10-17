#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <memory>
#include <vector>
#include <string>

class Component;
class Transform;
class Scene;

using namespace std;

class Entity
{
	friend class Engine;

public:
	shared_ptr<Transform> m_transform;

	string GetName();
	/*ON HOLD
	static weak_ptr<Entity> CreateEntity();
	static weak_ptr<Entity> FindEntity(string _name);
	*/

private:
	string m_name;
	vector<shared_ptr<Component>> m_components;
	//ON HOLD static weak_ptr<Scene> m_scene;

	void Create(weak_ptr<Scene> _currScene);
	void Update();
	//void Render(); may not be neccessary depends on rendering engine 
	void Awake();
	void Destroy();
	//further functions can be added here
	//bool Load(params); for level loading

};



#endif