#pragma once

#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Material.h"
#include "LightManager.h"
#include <glm/mat4x4.hpp>

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();
	
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	
protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram	m_shader;
	aie::OBJMesh        m_testMesh;
	Material            m_testMat;
	aie::Texture*       m_spearTex = nullptr;
	glm::mat4			m_meshTransform;
	LightManager* m_lights;
};