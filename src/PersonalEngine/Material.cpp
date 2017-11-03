#include "Material.h"
#include "Texture.h"

void Material::SetTexture(std::string _uniformName, std::string _filepath)
{
	if(m_textures.count(_uniformName))
	{
		std::weak_ptr<Texture> tex = Resource::FindResource<Texture>(_filepath);
		if (tex.expired())
		{
			tex = Texture::LoadImage(_filepath);
		}

		m_textures.at(_uniformName) = tex.lock()->GetTexIndex();
	}

}

void Material::SetMat4(std::string _uniformName, glm::mat4 _matrix)
{
	if(m_matrix4s.count(_uniformName))
	{
		m_matrix4s.at(_uniformName) = _matrix;
	}
}

void Material::SetVec3(std::string _uniformName, glm::vec3 _vector)
{
	if(m_vector3s.count(_uniformName))
	{
		m_vector3s.at(_uniformName) = _vector;
	}
}

void Material::SetVec4(std::string _uniformName, glm::vec4 _vector)
{
	if(m_vector4s.count(_uniformName))
	{
		m_vector4s.at(_uniformName) = _vector;
	}
}

void Material::SetFloat(std::string _uniformName, float _float)
{
	if(m_floats.count(_uniformName))
	{
		m_floats.at(_uniformName) = _float;
	}
}

void Material::SetInt(std::string _uniformName, int _int)
{
	if(m_ints.count(_uniformName))
	{
		m_ints.at(_uniformName) = _int;
	}
}

void Material::SetBool(std::string _uniformName, bool _bool)
{
	if(m_bools.count(_uniformName))
	{
		m_bools.at(_uniformName) = _bool;
	}
}