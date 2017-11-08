#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>

Material::Material(std::weak_ptr<Shader> _shader, std::string _name)
{
	m_name = _name;
	m_shader = _shader;
}

//When first setting a value in the material it checks whether the shader contains a uniform of the given name
//if it does it compares it to the type of uniform that the specific container can handle
//if it fits then it will create an entry for the uniform in the material's container
//this means that it will not try to access a non-existent uniform, it will not store data of the wrong type for a given uniform
//and allows some uniforms to not be given values resulting in them taking the default value given in the shader program
void Material::SetTexture(std::string _uniformName, std::weak_ptr<Texture> _texture)
{
	if(m_textures.count(_uniformName))
	{
		m_textures.at(_uniformName) = _texture.lock()->GetTexIndex();
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_SAMPLER_2D)
		{
			m_textures.emplace(_uniformName, _texture.lock()->GetTexIndex());
		}
	}

}

void Material::SetMat4(std::string _uniformName, glm::mat4 _matrix)
{
	if(m_matrix4s.count(_uniformName))
	{
		m_matrix4s.at(_uniformName) = _matrix;
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_FLOAT_MAT4)
		{
			m_matrix4s.emplace(_uniformName, _matrix);
		}
	}
}

void Material::SetVec3(std::string _uniformName, glm::vec3 _vector)
{
	if(m_vector3s.count(_uniformName))
	{
		m_vector3s.at(_uniformName) = _vector;
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_FLOAT_VEC3)
		{
			m_vector3s.emplace(_uniformName, _vector);
		}
	}
}

void Material::SetVec4(std::string _uniformName, glm::vec4 _vector)
{
	if(m_vector4s.count(_uniformName))
	{
		m_vector4s.at(_uniformName) = _vector;
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_FLOAT_VEC4)
		{
			m_vector4s.emplace(_uniformName, _vector);
		}
	}
}

void Material::SetFloat(std::string _uniformName, float _float)
{
	if(m_floats.count(_uniformName))
	{
		m_floats.at(_uniformName) = _float;
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_FLOAT)
		{
			m_floats.emplace(_uniformName, _float);
		}
	}
}

void Material::SetInt(std::string _uniformName, int _int)
{
	if(m_ints.count(_uniformName))
	{
		m_ints.at(_uniformName) = _int;
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_INT)
		{
			m_ints.emplace(_uniformName, _int);
		}
	}
}

void Material::SetBool(std::string _uniformName, bool _bool)
{
	if(m_bools.count(_uniformName))
	{
		m_bools.at(_uniformName) = _bool;
	}
	else if(m_shader.lock()->m_uniforms.count(_uniformName))
	{
		if(m_shader.lock()->m_uniforms.at(_uniformName).type == GL_BOOL)
		{
			m_bools.emplace(_uniformName, _bool);
		}
	}
}

void Material::ReadyForDraw()
{
	glUseProgram(m_shader.lock()->GetProgram());

	for( auto i = m_matrix4s.begin(); i != m_matrix4s.end(); i++)
	{
		glUniformMatrix4fv(m_shader.lock()->m_uniforms.at(i->first).location,1,GL_FALSE,glm::value_ptr(i->second));
	}
	for( auto i = m_vector3s.begin(); i != m_vector3s.end(); i++)
	{
		glUniform3fv(m_shader.lock()->m_uniforms.at(i->first).location,1,glm::value_ptr(i->second));
	}
	for( auto i = m_vector4s.begin(); i != m_vector4s.end(); i++)
	{
		glUniform4fv(m_shader.lock()->m_uniforms.at(i->first).location,1,glm::value_ptr(i->second));
	}
	for( auto i = m_floats.begin(); i != m_floats.end(); i++)
	{
		glUniform1f(m_shader.lock()->m_uniforms.at(i->first).location,i->second);
	}
	for( auto i = m_ints.begin(); i != m_ints.end(); i++)
	{
		glUniform1i(m_shader.lock()->m_uniforms.at(i->first).location,i->second);
	}
	for( auto i = m_bools.begin(); i != m_bools.end(); i++)
	{
		glUniform1i(m_shader.lock()->m_uniforms.at(i->first).location,i->second);
	}
	int texCount = 0;
	for( auto i = m_textures.begin(); i != m_textures.end(); i++)
	{
		glUniform1i(m_shader.lock()->m_uniforms.at(i->first).location, texCount);
		glActiveTexture(GL_TEXTURE0+texCount);
		glBindTexture(GL_TEXTURE_2D,i->second);
		texCount++;
	}





}