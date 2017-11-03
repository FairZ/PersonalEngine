#ifndef _SHADER_H_
#define _SHADER_H_
#include "Resource.h"
#include <GL/glew.h>
#include <map>

struct UniformInfo
{
	GLint location;
	GLenum type;
	UniformInfo(GLint _location, GLenum _type)
	{
		location = _location;
		type = _type;
	}
};

class Shader : public Resource
{
	friend class Material;
public:
	//change out constructor for static void CreateShader()
	Shader(std::string _name, const char* _vertTXT, const char* _fragTXT);
	bool GetCompiled(){return m_compiled;}
	
protected:
	bool m_compiled;
	GLint m_program;
	std::map<std::string, UniformInfo> m_uniforms;//dictionary of uniforms and their locations
	const GLchar* m_vertex;
	const GLchar* m_fragment;

	std::string LoadShader(const char* _fileName);
};



#endif