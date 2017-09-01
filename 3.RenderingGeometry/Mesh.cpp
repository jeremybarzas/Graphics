#include "Mesh.h"
#include <gl_core_4_4.h>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::create_buffers()
{
	/*========== Generate Buffer Objects ==========*/
	// generate Vertex Buffer Object
	glGenBuffers(1, &m_vbo);

	// generate Index Buffer Object
	glGenBuffers(1, &m_ibo);

	// generate Vertex Array Object
	glGenVertexArrays(1, &m_vao);
}

void Mesh::initialize(std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	setVertices(verts);
	setIndices(indices);
}

void Mesh::bind()
{
	/*========== Bind Buffer Objects ==========*/
	// bind Vertex Array Object
	glBindVertexArray(m_vao);

	// bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// bind Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void Mesh::unbind()
{
	/*========== Cleanup Buffer Objects ==========*/
	// clear the Vertex Array Object bind
	glBindVertexArray(0);

	// clear the Vertex Buffer Object bind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// clear the Index Buffer Object bind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::startup_portion()
{
	/*========== Order ==========*/

	// generate vertex array object
	//	- m_vao
	// generate buffer objects
	//	- m_vbo
	//	- m_ibo
	create_buffers();
	set_vertex_and_index_data();
	initialize(m_vertices, m_indices);

	// buffer objects data
	//	- m_vbo
	//	- m_ibo
	bind();

	// vertex specification
	//  - pos
	//	- color
	//  - uv
	//  - normal
	//  - etc..

	// unbind vertex array object
	//	- glBindVertexArray(m_vao) to 0
	// unbind vertex buffer object
	//  - glBindBuffer(GL_ARRAY_BUFFER, m_vbo) to 0
	// unbind index buffer object
	//  - glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo) to 0
	unbind();

	// delete vertex and index arrays
	//	- m_vertices
	//	- m_indices
}

void Mesh::draw_portion()
{
	// bind vertex array object
	glBindVertexArray(m_vao);

	// set to draw wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// draws each element
	unsigned int indexCount = m_index_count;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	// unbind vertex array object
	glBindVertexArray(0);
}

void Mesh::set_vertex_and_index_data()
{
	// populate vert and index arrays
	Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) }; //bottom left	
	Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //bottom right
	Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) }; //top left
	Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) }; //top right
	Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) }; //top right	

	std::vector<Vertex> m_vertices{ a,b,c,d,e };
	std::vector<unsigned int> m_indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };
}

void Mesh::setVertices(std::vector<Vertex> vertices)
{
	m_vertices = vertices;

	m_vertex_count = m_vertices.size();
}

void Mesh::setIndices(std::vector<unsigned int> indices)
{
	m_indices = indices;

	m_index_count = m_indices.size();
}

std::vector<Vertex> Mesh::getVertices()
{
	return m_vertices;
}

std::vector<unsigned int> Mesh::getIndices()
{
	return m_indices;
}

void Mesh::binder(unsigned int bind, bool check)
{
	/*========== Bind Buffer Objects ==========*/

	// bind or unbind Vertex Array Object
	if (bind == m_vao)
	{
		if(check == true)
			glBindVertexArray(m_vao);
		else
			glBindVertexArray(0);
		return;
	}

	// bind or unbind Vertex Buffer Object
	if (bind == m_vao)
	{
		if (check == true)
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		else
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		return;
	}

	// bind  or unbind Index Buffer Object
	if (bind == m_vao)
	{
		if (check == true)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		else
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		return;
	}
}

void Mesh::vao_binder(bool check)
{
	if (check == true)
	{
		// bind Vertex Array Object
		glBindVertexArray(m_vao);	
	}
	else
	{
		// clear vertex array object bind
		glBindVertexArray(0);
	}	
}

void Mesh::vbo_binder(bool check)
{
	if (check == true)
	{
		// bind vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}
	else
	{
		// clear vertex buffer object bind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Mesh::ibo_binder(bool check)
{
	if (check == true)
	{
		// bind index buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	}
	else
	{
		// clear index buffer object bind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}