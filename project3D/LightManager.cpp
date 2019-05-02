#include "LightManager.h"
#include "gl_core_4_4.h"
#include <string>

using namespace glm;

LightManager::LightManager(aie::ShaderProgram* lightShader)
{
	m_shader = lightShader;

	m_lightCount = 0;

	m_lightCountUniformHandle = -1;

	if (m_shader) 
	{
		glUseProgram(m_shader->getHandle());

		// Get light uniform locations.
		m_lightCountUniformHandle = glGetUniformLocation(m_shader->getHandle(), "lightCount");
	}
}

LightManager::~LightManager()
{

}

void LightManager::AddLight(const vec4& position, const vec3& color, const float& radius) 
{
	if (m_lightCount >= 8)
		return;

	Light& light = m_lights[m_lightCount];

	light.position = position;
	light.color = color;
	light.radius = radius;

	m_lightCount++;
}

void LightManager::Update() 
{
	if (!m_shader)
		return;
	
	glUseProgram(m_shader->getHandle());

	// Send light data.
	for(int i = 0; i < m_lightCount; ++i) 
	{
		std::string name = "lights[" + std::to_string(i) + "]";

		int posLoc = glGetUniformLocation(m_shader->getHandle(), (name + ".position").c_str());
		int colLoc = glGetUniformLocation(m_shader->getHandle(), (name + ".color").c_str());
		int radLoc = glGetUniformLocation(m_shader->getHandle(), (name + ".radius").c_str());

		glUniform4fv(posLoc, sizeof(float), (float*)(&m_lights[i].position));
		glUniform3fv(colLoc, sizeof(float), (float*)(&m_lights[i].color));
		glUniform1f(radLoc, m_lights[i].radius);
	}
	
	// Send light count.
	glUniform1i(m_lightCountUniformHandle, m_lightCount);

	glUseProgram(0);
}
