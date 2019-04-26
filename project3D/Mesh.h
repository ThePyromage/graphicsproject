#pragma once
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void initialiseQuad();

	virtual void draw();

protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

