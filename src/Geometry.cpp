#include "Geometry.h"

/*Geometry Geometry::fromCube(float width, float height, float depth) {
	static Geometry geometry;
	float v[] = {width/2, -height/2, -depth/2, 0, 0, -1, 0, 0,
				   -width/2, -height/2, -depth/2, 0, 0, -1, 1, 0,
				   -width/2, height/2, -depth/2, 0, 0, -1, 1, 1,
				   width/2, height/2, -depth/2, 0, 0, -1, 0, 1,
				   -width/2, -height/2, depth/2, 0, 0, 1, 0, 0,
				   width/2, -height/2, depth/2, 0, 0, 1, 1, 0,
				   width/2, height/2, depth/2, 0, 0, 1, 1, 1,
				   -width/2, height/2, depth/2, 0, 0, 1, 0, 1,
				   -width/2, -height/2, -depth/2, -1, 0, 0, 0, 0,
				   -width/2, -height/2, depth/2, -1, 0, 0, 1, 0,
				   -width/2, height/2, depth/2, -1, 0, 0, 1, 1,
				   -width/2, height/2, -depth/2, -1, 0, 0, 0, 1,
				   width/2, -height/2, depth/2, 1, 0, 0, 0, 0,
				   width/2, -height/2, -depth/2, 1, 0, 0, 1, 0,
				   width/2, height/2, -depth/2, 1, 0, 0, 1, 1,
				   width/2, height/2, depth/2, 1, 0, 0, 0, 1,
				   width/2, height/2, -depth/2, 0, 1, 0, 0, 0,
				   -width/2, height/2, -depth/2, 0, 1, 0, 1, 0,
				   -width/2, height/2, depth/2, 0, 1, 0, 1, 1,
				   width/2, height/2, depth/2, 0, 1, 0, 0, 1,
				   -width/2, -height/2, -depth/2, 0, -1, 0, 0, 0,
				   width/2, -height/2, -depth/2, 0, -1, 0, 1, 0,
				   width/2, -height/2, depth/2, 0, -1, 0, 1, 1,
				   -width/2, -height/2, depth/2, 0, -1, 0, 0, 1};

	unsigned int i[] = {0, 1, 2,
				  0, 2, 3,
				  4, 5, 6,
				  4, 6, 7,
				  8, 9, 10,
				  8, 10, 11,
				  12, 13, 14,
				  12, 14, 15,
				  16, 17, 18,
				  16, 18, 19,
				  20, 21, 22,
				  20, 22, 23};
	
	std::vector<float> vertices(&v[0], &v[0]+192);
	std::vector<unsigned int> indices(&i[0], &i[0]+36);

	geometry.m_vertices = vertices;
	geometry.m_indices = indices;

	return geometry;
}*/

Geometry::Geometry(void) {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

Geometry::~Geometry(void) {

}

void Geometry::init(const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texcoords, const std::vector<unsigned int>& indices, const std::vector<glm::vec3>& normals) {
	initVertices(positions, texcoords, indices, normals);
}

void Geometry::initVertices(std::vector<glm::vec3> positions, std::vector<glm::vec2> texcoords, std::vector<unsigned int> indices, std::vector<glm::vec3> normals) {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	if (positions.size() == texcoords.size()) {
		std::vector<glm::vec3> tangents;
		
		if (positions.size() == normals.size()) {
			tangents.resize(positions.size());
			std::vector<glm::vec3> tan1;
			std::vector<glm::vec3> tan2;
			tan1.resize(positions.size());
			tan2.resize(positions.size());
			for (unsigned int i = 0; i < indices.size(); i += 3) {
				glm::vec3 pos1 = positions[indices[i]];
				glm::vec3 pos2 = positions[indices[i + 1]];
				glm::vec3 pos3 = positions[indices[i + 2]];
				glm::vec3 n1 = pos2 - pos1;
				glm::vec3 n2 = pos3 - pos1;

				glm::vec2 tex1 = texcoords[indices[i]];
				glm::vec2 tex2 = texcoords[indices[i + 1]];
				glm::vec2 tex3 = texcoords[indices[i + 2]];
				float s1 = tex2.x - tex1.x;
				float t1 = tex2.y - tex1.y;
				float s2 = tex3.x - tex1.x;
				float t2 = tex3.y - tex1.y;

				float r = 1.0f / (s1 * t2 - s2 * t1);

				glm::vec3 sdir((t2 * n1.x - t1 * n2.x) * r, (t2 * n1.y - t1 * n2.y) * r, (t2 * n1.z - t1 * n2.z) * r);
				glm::vec3 tdir((s1 * n2.x - s2 * n1.x) * r, (s1 * n2.y - s2 * n1.y) * r, (s1 * n2.z - s2 * n1.z) * r);

				tan1[indices[i]] += sdir;
				tan1[indices[i + 1]] += sdir;
				tan1[indices[i + 2]] += sdir;

				tan2[indices[i]] += tdir;
				tan2[indices[i + 1]] += tdir;
				tan2[indices[i + 2]] += tdir;
			}

			for (unsigned int i = 0; i < positions.size(); ++i) {
				glm::vec3 n = normals[i];
				glm::vec3 t = tan1[i];

				tangents[i] = glm::normalize(t - n * glm::dot(n, t));
				if (glm::dot(glm::cross(n, t), tan2[i]) < 0.0f) {
					tangents[i] = glm::vec3(-tangents[i].x, -tangents[i].y, -tangents[i].z);
				}
			}
		} else {
			normals.clear();
			normals.resize(positions.size());
			tangents.resize(positions.size());
			for (unsigned int i = 0; i < indices.size(); i += 3) {
				glm::vec3 pos1 = positions[indices[i]];
				glm::vec3 pos2 = positions[indices[i + 1]];
				glm::vec3 pos3 = positions[indices[i + 2]];
				glm::vec3 n1 = pos2 - pos1;
				glm::vec3 n2 = pos3 - pos1;
				glm::vec3 normal = glm::normalize(glm::vec3(n1.y * n2.z - n1.z * n2.y, n1.z * n2.x - n1.x * n2.z, n1.x * n2.y - n1.y * n2.x));
			
				normals[indices[i]] = normal;
				normals[indices[i + 1]] = normal;
				normals[indices[i + 2]] = normal;

				glm::vec2 tex1 = texcoords[indices[i]];
				glm::vec2 tex2 = texcoords[indices[i + 1]];
				glm::vec2 tex3 = texcoords[indices[i + 2]];
				float t1 = tex2.x - tex1.x;
				float b1 = tex2.y - tex1.y;
				float t2 = tex3.x - tex1.x;
				float b2 = tex3.y - tex1.y;
				glm::vec3 tangent = glm::normalize(glm::vec3(b2 * n1.x - b1 * n2.x, b2 * n1.y - b1 * n2.y, b2 * n1.z - b1 * n2.z));
				
				tangents[indices[i]] = tangent;
				tangents[indices[i + 1]] = tangent;
				tangents[indices[i + 2]] = tangent;
			}
		}
		
		for (unsigned int i = 0; i < positions.size(); ++i) {
			m_vertices.push_back(positions[i].x);
			m_vertices.push_back(positions[i].y);
			m_vertices.push_back(positions[i].z);
			m_vertices.push_back(texcoords[i].x);
			m_vertices.push_back(texcoords[i].y);
			m_vertices.push_back(normals[i].x);
			m_vertices.push_back(normals[i].y);
			m_vertices.push_back(normals[i].z);
			m_vertices.push_back(tangents[i].x);
			m_vertices.push_back(tangents[i].y);
			m_vertices.push_back(tangents[i].z);
		}
		m_indices = indices;
	}
}

void Geometry::smoothenNormals(float epsilon) {
	for (unsigned int i = 0; i < m_vertices.size(); i += 11) {
		for (unsigned int j = 0; j <  m_vertices.size(); j += 11) {
			glm::vec3 position1(m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]);
			glm::vec3 position2(m_vertices[j], m_vertices[j + 1], m_vertices[j + 2]);
			glm::vec3 normal1(m_vertices[i + 5], m_vertices[i + 6], m_vertices[i + 7]);
			glm::vec3 normal2(m_vertices[j + 5], m_vertices[j + 6], m_vertices[j + 7]);
			glm::vec3 tangent1(m_vertices[i + 8], m_vertices[i + 9], m_vertices[i + 10]);
			glm::vec3 tangent2(m_vertices[j + 8], m_vertices[j + 9], m_vertices[j + 10]);
			if (glm::length(position1 - position2) < epsilon) {
				glm::vec3 normal = glm::normalize((normal1 + normal2) / 2.0f);
				m_vertices[i + 5] = normal.x;
				m_vertices[i + 6] = normal.y;
				m_vertices[i + 7] = normal.z;
				m_vertices[j + 5] = normal.x;
				m_vertices[j + 6] = normal.y;
				m_vertices[j + 7] = normal.z;

				glm::vec3 tangent = glm::normalize((tangent1 + tangent2) / 2.0f);
				m_vertices[i + 8] = tangent.x;
				m_vertices[i + 9] = tangent.y;
				m_vertices[i + 10] = tangent.z;
				m_vertices[j + 8] = tangent.x;
				m_vertices[j + 9] = tangent.y;
				m_vertices[j + 10] = tangent.z;
			}
		}
	}
}

void Geometry::scale(float scale) {
	for (unsigned int i = 0; i < m_vertices.size(); i += 11) {
		m_vertices[i] *= scale;
		m_vertices[i + 1] *= scale;
		m_vertices[i + 2] *= scale;
	}
}

std::vector<glm::vec3> Geometry::getIndexedPositions(void) {
	std::vector<glm::vec3> positions;
	for (unsigned int i = 0; i < m_indices.size(); ++i) {
		positions.push_back(glm::vec3(m_vertices[m_indices[i] * 11], m_vertices[m_indices[i] * 11 + 1], m_vertices[m_indices[i] * 11 + 2]));
	}
	return positions;
}

std::vector<float>& Geometry::getVertices(void) {
	return m_vertices;
}

std::vector<unsigned int>& Geometry::getIndices(void) {
	return m_indices;
}

BoundingBox Geometry::getBoundingBox(void) {
	return m_boundingBox;
}

BoundingSphere Geometry::getBoundingSphere(void) {
	return m_boundingSphere;
}

void Geometry::createBuffers(void) {
	if (m_vertexBuffer == 0) createVertexBuffer();
	if (m_indexBuffer == 0) createIndexBuffer();
}

void Geometry::deleteBuffers(void) {
	if (m_vertexBuffer != 0) glDeleteBuffers(1, &m_vertexBuffer);
	if (m_indexBuffer != 0) glDeleteBuffers(1, &m_indexBuffer);
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

void Geometry::createVertexBuffer(void) {
	if (m_vertices.size() > 0) {
		glm::vec3 min(m_vertices[0], m_vertices[1], m_vertices[2]);
		glm::vec3 max(m_vertices[0], m_vertices[1], m_vertices[2]);

		for (unsigned int i = 0; i < m_vertices.size(); i += 11) {
			if (m_vertices[i] < min.x) min.x = m_vertices[i];
			if (m_vertices[i+1] < min.y) min.y = m_vertices[i+1];
			if (m_vertices[i+2] < min.z) min.z = m_vertices[i+2];

			if (m_vertices[i] > max.x) max.x = m_vertices[i];
			if (m_vertices[i+1] > max.y) max.y = m_vertices[i+1];
			if (m_vertices[i+2] > max.z) max.z = m_vertices[i+2];
		}
	
		m_boundingBox.min = min;
		m_boundingBox.max = max;

		glm::vec3 center = (min + max) / 2.0f;

		float maxRadius = 0;
		for (unsigned int i = 0; i < m_vertices.size(); i += 11) {
			float x = m_vertices[i] - center.x;
			float y = m_vertices[i+1] - center.y;
			float z = m_vertices[i+1] - center.z;
			float radius = glm::sqrt(x*x + y*y + z*z);
			if (maxRadius < radius) maxRadius = radius;
		}

		m_boundingSphere.center = center;
		m_boundingSphere.radius = maxRadius;

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Geometry::createIndexBuffer(void) {
	if (m_indices.size() > 0) {
		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Geometry::bind(ShaderProgram *shader) {
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	const GLchar* pointer = 0;

	m_positionLocation = shader->getAttributeLocation("position");
	glVertexAttribPointer(m_positionLocation, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), pointer);
	glEnableVertexAttribArray(m_positionLocation);

	m_texcoordLocation = shader->getAttributeLocation("texcoord");
	glVertexAttribPointer(m_texcoordLocation, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), pointer + 3 * sizeof(GLfloat));
	glEnableVertexAttribArray(m_texcoordLocation);

	m_normalLocation = shader->getAttributeLocation("normal");
	glVertexAttribPointer(m_normalLocation, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), pointer + 5 * sizeof(GLfloat));
	glEnableVertexAttribArray(m_normalLocation);

	m_tangentLocation = shader->getAttributeLocation("tangent");
	glVertexAttribPointer(m_tangentLocation, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), pointer + 8 * sizeof(GLfloat));
	glEnableVertexAttribArray(m_tangentLocation);
}

void Geometry::unbind(void) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(m_positionLocation);
	glDisableVertexAttribArray(m_texcoordLocation);
	glDisableVertexAttribArray(m_normalLocation);
	glDisableVertexAttribArray(m_tangentLocation);
}

void Geometry::render(ShaderProgram* shader) {
	bind(shader);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*) 0);
	unbind();
}