#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#include <string>
#include <memory>

class Scene;

/// \brief Abstract base class for resources
class Resource
{
public:
	std::string GetName(){return m_name;}
protected:
	std::string m_name;	
};


#endif