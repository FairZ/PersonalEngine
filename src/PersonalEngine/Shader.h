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

/// \brief Resource which handles the loading, compiling and storing of shader programs
class Shader : public Resource
{
	friend class Material;
	friend class RenderController;
public:
	/// \private
	Shader(std::string _name, const char* _vertTXT, const char* _fragTXT);
	/// \private
	~Shader();

	bool GetCompiled(){return m_compiled;}
	GLint GetProgram(){return m_program;}
	
protected:
	bool m_compiled;
	GLint m_program;
	std::map<std::string, UniformInfo> m_uniforms;//dictionary of uniforms and their locations
	const GLchar* m_vertex;
	const GLchar* m_fragment;

	std::string LoadShader(const char* _fileName);
};



#endif