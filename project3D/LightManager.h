#pragma once
#include "Shader.h"
#include <glm/glm.hpp>

class LightManager
{
public:

	struct Light
	{
		glm::vec4 position;
		glm::vec3 color;
		float radius;
	};

	LightManager(aie::ShaderProgram* lightShader);

	~LightManager();

	void AddLight(const glm::vec4& position, const glm::vec3& color, const float& radius);

	void Update();

private:

	aie::ShaderProgram* m_shader;

	int m_lightCountUniformHandle;

	Light m_lights[8];
	unsigned int m_lightCount;
};

