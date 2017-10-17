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
	unsigned char GetLayer();
	static weak_ptr<Entity> CreateEntity();
	//static weak_ptr<Entity> FindEntity(string _name);


private:
	string m_name;
	unsigned char m_layer;
	vector<shared_ptr<Component>> m_components;
	static weak_ptr<Scene> m_scene;

	void Update();
	//void Render(); may not be neccessary depends on rendering engine 
	void Awake();
	void Destroy();
	//further functions can be added here
	//bool Load(params); for level loading

};



#endif