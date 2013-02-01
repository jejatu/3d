#include "Mesh.h"

Mesh::Mesh(void) : Object3d() {
	geometry = 0;
	material = 0;
	bothSides = false;
}

Mesh::~Mesh(void) {

}

void Mesh::init(Geometry* geometry, Material* material) {
	this->geometry = geometry;
	this->material = material;
	m_boundingBox = this->geometry->getBoundingBox();
	m_boundingSphere = this->geometry->getBoundingSphere();
}

void Mesh::render(ShaderProgram* shader) {
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(m_transform));
	material->bind(shader);
	geometry->render(shader);
	material->unbind();
}