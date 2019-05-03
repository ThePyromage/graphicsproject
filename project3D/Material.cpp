#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include <string>
#include "gl_core_4_4.h"

Material::Material() 
{
	//set shader to null if none provided
	m_shader = nullptr;
}

Material::Material(aie::ShaderProgram* shader)
{
	//assign shader
	m_shader = shader;

	//if no shader provided, cancel
	if (!m_shader)
		return;

	//get program for shader
	glUseProgram(m_shader->getHandle());

	for (int i = 0; i < 16; ++i)
	{
		//get texturemaps uniform handle
		std::string name = "textureMaps[" + std::to_string(i) + "]";

		int uniformHandle = glGetUniformLocation(m_shader->getHandle(), name.c_str());

		glUniform1i(uniformHandle, i);
	}

}

Material::~Material()
{
	
}

void Material::AddMap(aie::Texture* texture) 
{
	//add texture to list
	m_textureMaps.push_back(texture);
}

void Material::Bind() 
{
	// Uses the shader.
	glUseProgram(m_shader->getHandle());

	// Bind all texture maps.
	for(int i = 0; i < m_textureMaps.size(); ++i) 
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureMaps[i]->getHandle());
	}
	
	glActiveTexture(GL_TEXTURE0);
}