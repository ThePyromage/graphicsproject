#include "LightManager.h"
#include "gl_core_4_4.h"
#include <string>

using namespace glm;

LightManager::LightManager(aie::ShaderProgram* lightShader)
{
	//get shaders
	m_shader = lightShader;

	//set light count to zero
	m_lightCount = 0;

	//set light count uniform handle to default
	m_lightCountUniformHandle = -1;

	//if we have a shader, get data from it
	if (m_shader) 
	{
		//get shader handle
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
	//if at max lights, return
	if (m_lightCount >= 8)
		return;
	
	//add new light
	m_lightPositions[m_lightCount] = position;
	m_lightColours[m_lightCount] = color;
	m_lightRadiuses[m_lightCount] = radius;

	//increment light count
	m_lightCount++;
}

void LightManager::Update() 
{
	//if no shader ignore this code
	if (!m_shader)
		return;
	
	glUseProgram(m_shader->getHandle());

	// Send light data.
	for(unsigned int i = 0; i < m_lightCount; ++i) 
	{
		//Get uniform locations for light data
		int posLoc = glGetUniformLocation(m_shader->getHandle(), ("lightPositions[" + std::to_string(i) + "]").c_str());
		int colLoc = glGetUniformLocation(m_shader->getHandle(), ("lightColours[" + std::to_string(i) + "]").c_str());
		int radLoc = glGetUniformLocation(m_shader->getHandle(), ("lightRadiuses[" + std::to_string(i) + "]").c_str());

		//send light data to GPU
		glUniform4fv(posLoc, 1, (float*)(&m_lightPositions[i]));
		glUniform3fv(colLoc, 1, (float*)(&m_lightColours[i]));
		glUniform1f(radLoc, m_lightRadiuses[i]);
	}
	
	// Send light count.
	glUniform1i(m_lightCountUniformHandle, m_lightCount);

	glUseProgram(0);
}
