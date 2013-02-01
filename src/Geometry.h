#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

class Geometry {
public:
	Geometry(void);
	~Geometry(void);
	void init(const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texcoords, const std::vector<unsigned int>& indices, const std::vector<glm::vec3>& normals = std::vector<glm::vec3>());
	void bind(ShaderProgram *shader);
	void unbind(void);
	void render(ShaderProgram* shader);
	void scale(float scale);
	void smoothenNormals(float epsilon = 0.001f);
	void createBuffers(void);
	void deleteBuffers(void);
	std::vector<glm::vec3> getIndexedPositions(void);
	std::vector<float>& getVertices(void);
	std::vector<unsigned int>& getIndices(void);
	BoundingBox getBoundingBox(void);
	BoundingSphere getBoundingSphere(void);

protected:
	void initVertices(std::vector<glm::vec3> positions, std::vector<glm::vec2> texcoords, std::vector<unsigned int> indices, std::vector<glm::vec3> normals = std::vector<glm::vec3>());
	void createVertexBuffer(void);
	void createIndexBuffer(void);

	std::vector<GLfloat> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	BoundingBox m_boundingBox;
	BoundingSphere m_boundingSphere;
	GLint m_positionLocation;
	GLint m_texcoordLocation;
	GLint m_normalLocation;
	GLint m_tangentLocation;
};

