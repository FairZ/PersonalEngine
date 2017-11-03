#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#include <string>
#include <memory>

class Scene;

class Resource
{
public:
	std::string GetName(){return m_name;}
protected:
	std::string m_name;

	static std::weak_ptr<Scene> m_scene;

	//TODO FIND A WAY TO ACCESS RESOURCES BY SUBCLASS EITHER THROUGH CHANGING WHERE THEY ARE STORED OR ANOTHER METHOD
	static std::weak_ptr<T>FindResource(std::string _name);
	
};


#endif