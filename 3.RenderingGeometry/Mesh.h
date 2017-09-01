#pragma once
#include <vector>
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	unsigned int m_index_count;
	unsigned int m_vertex_count;

	void create_buffers();
	void initialize(std::vector<Vertex> &verts, std::vector<unsigned int> &indices);
	void bind();
	void unbind();	

	/*===== custom functions =====*/

	// order of operations templates
	void startup_portion();
	void draw_portion();
		
	// get & set value functions
	std::vector<Vertex> getVertices();
	std::vector<unsigned int> getIndices();
	void setVertices(std::vector<Vertex>);
	void setIndices(std::vector<unsigned int>);	

	// helper functions
	void set_vertex_and_index_data();
	void binder(unsigned int, bool);	
	void vao_binder(bool);
	void vbo_binder(bool);
	void ibo_binder(bool);

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
