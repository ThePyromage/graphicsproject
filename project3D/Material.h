#pragma once
#include <vector>

namespace aie 
{
	class ShaderProgram;
	class Texture;
};

class Material
{
public:

	Material();

	Material(aie::ShaderProgram* shader);

	~Material();

	/*
	Description: Add a texture map to be used when drawing with this material.
	Param:
	    aie::Texture* texture: The texture map to reference. 
	*/
	void AddMap(aie::Texture* texture);

	/*
	Description: Bind the texturemaps and shader of this material for use in drawing.
	*/
	void Bind();

private:

	aie::ShaderProgram* m_shader;
	std::vector<aie::Texture*> m_textureMaps;
};

