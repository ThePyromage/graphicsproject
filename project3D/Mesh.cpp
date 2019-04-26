#include "Mesh.h"
#include <glm/glm.hpp>
#include <gl_core_4_4.h>

Mesh::Mesh()
{
	vao = 0;
	vbo = 0;
	ibo = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	//check that the mesh is not initialised already
	assert(vao == 0);

	//generate buffers
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//define 6 vertices for 2 triangles

	/*
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };
	*/

	Vertex vertices[4];

	vertices[0].position = { -0.5f, 0.0f, 0.5f, 1.0f };
	vertices[1].position = { 0.5f, 0.0f, 0.5f, 1.0f };
	vertices[2].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	vertices[3].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//enable first element as position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	unsigned int indices[6] =
	{
		0, 1, 2, //  Triangle 1
		1, 3, 2 // Triangle 2
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	//using indices or just vertices?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}
