#pragma once
#include "Shader.h"
#include <glm/glm.hpp>

class LightManager
{
public:
	//constructor
	LightManager(aie::ShaderProgram* lightShader);

	//destructor, not used for anything
	~LightManager();

	//add new light, takes in position, colour and radius
	void AddLight(const glm::vec4& position, const glm::vec3& color, const float& radius);

	//update function
	void Update();

private:

	//lighting shader
	aie::ShaderProgram* m_shader;

	//handle for light count uniform
	int m_lightCountUniformHandle;

	//light data
	glm::vec4 m_lightPositions[8];
	glm::vec3 m_lightColours[8];
	float m_lightRadiuses[8];

	//how many lights we have
	unsigned int m_lightCount;
};

