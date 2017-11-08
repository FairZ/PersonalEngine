#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "Resource.h"
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader;
class Texture;

class Material : public Resource
{
public:
	Material(std::weak_ptr<Shader> _shader, std::string _name);
	
	void SetTexture(std::string _uniformName, std::weak_ptr<Texture> _texture);
	void SetMat4(std::string _uniformName, glm::mat4 _matrix);
	void SetVec3(std::string _uniformName, glm::vec3 _vector);
	void SetVec4(std::string _uniformName, glm::vec4 _vector);
	void SetFloat(std::string _uniformName, float _float);
	void SetInt(std::string _uniformName, int _int);
	void SetBool(std::string _uniformName, bool _bool);

	void ReadyForDraw();

private:
	std::weak_ptr<Shader> m_shader;

	std::map<std::string, GLint> m_textures;
	std::map<std::string, glm::mat4> m_matrix4s;
	std::map<std::string, glm::vec3> m_vector3s;
	std::map<std::string, glm::vec4> m_vector4s;
	std::map<std::string, float> m_floats;
	std::map<std::string, int> m_ints;
	std::map<std::string, bool> m_bools;
};

#endif