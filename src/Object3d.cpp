#include "Object3d.h"

Object3d::Object3d(void) {

}

Object3d::~Object3d(void) {

}

void Object3d::translate(float x, float y, float z) {
	m_transform = glm::translate(m_transform, glm::vec3(x, y, z));
}

void Object3d::translate(const glm::vec3& translation) {
	m_transform = glm::translate(m_transform, translation);
}

void Object3d::rotate(const glm::vec3& axis, float angle) {
	m_transform = glm::rotate(m_transform, angle, axis);
}

void Object3d::scale(float x, float y, float z) {
	m_transform = glm::scale(m_transform, glm::vec3(x, y, z));
}

void Object3d::scale(const glm::vec3& scale) {
	m_transform = glm::scale(m_transform, scale);
}

void Object3d::scale(float scale) {
	m_transform = glm::scale(m_transform, glm::vec3(scale, scale, scale));
}

glm::mat3 Object3d::getRotationMatrix(void) {
	float scaleX = glm::sqrt(m_transform[0].x * m_transform[1].x + m_transform[1].x * m_transform[2].x + m_transform[2].x * m_transform[3].x);
	float scaleY = glm::sqrt(m_transform[0].y * m_transform[1].y + m_transform[1].y * m_transform[2].y + m_transform[2].y * m_transform[3].y);
	float scaleZ = glm::sqrt(m_transform[0].z * m_transform[1].z + m_transform[1].z * m_transform[2].z + m_transform[2].z * m_transform[3].z);
	glm::mat3 rotationMatrix;
	rotationMatrix[0].x = m_transform[0].x / scaleX;
	rotationMatrix[1].x = m_transform[1].x / scaleX;
	rotationMatrix[2].x = m_transform[2].x / scaleX;
	rotationMatrix[0].y = m_transform[0].y / scaleY;
	rotationMatrix[1].y = m_transform[1].y / scaleY;
	rotationMatrix[2].y = m_transform[2].y / scaleY;
	rotationMatrix[0].z = m_transform[0].y / scaleZ;
	rotationMatrix[1].z = m_transform[1].y / scaleZ;
	rotationMatrix[2].z = m_transform[2].y / scaleZ;
	return rotationMatrix;
}

glm::vec3 Object3d::getPosition(void) {
	return glm::vec3(m_transform[3].x, m_transform[3].y, m_transform[3].z);
}

glm::vec3 Object3d::getForward(void) {
	return glm::normalize(glm::vec3(-m_transform[2].x, -m_transform[2].y, -m_transform[2].z));
}

glm::vec3 Object3d::getUp(void) {
	return glm::normalize(glm::vec3(m_transform[1].x, m_transform[1].y, m_transform[1].z));
}

glm::vec3 Object3d::getRight(void) {
	return glm::normalize(glm::vec3(m_transform[0].x, m_transform[0].y, m_transform[0].z));
}

glm::mat4 Object3d::getTransform(void) {
	return m_transform;
}

BoundingBox Object3d::getBoundingBox(void) {
	return BoundingBox(m_boundingBox.min + getPosition(), m_boundingBox.max + getPosition());
}

BoundingSphere Object3d::getBoundingSphere(void) {
	return BoundingSphere(m_boundingSphere.center + getPosition(), m_boundingSphere.radius);
}

void Object3d::setPosition(float x, float y, float z) {
	glm::vec3 position(x, y, z);
	setPosition(position);
}

void Object3d::setPosition(const glm::vec3& position) {
	m_transform[3].x = position.x;
	m_transform[3].y = position.y;
	m_transform[3].z = position.z;
}

void Object3d::setTransform(const glm::mat4& transform) {
	m_transform = transform;
}