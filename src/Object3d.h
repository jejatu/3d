#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "BoundingBox.h"
#include "BoundingSphere.h"

class Object3d {
public:
	Object3d(void);
	~Object3d(void);
	void translate(float x, float y, float z);
	void translate(const glm::vec3& translation);
	void rotate(const glm::vec3& axis, float angle);
	void scale(float x, float y, float z);
	void scale(const glm::vec3& scale);
	void scale(float scale);
	glm::mat3 getRotationMatrix(void);
	virtual glm::vec3 getPosition(void);
	virtual glm::vec3 getForward(void);
	virtual glm::vec3 getUp(void);
	virtual glm::vec3 getRight(void);
	glm::mat4 getTransform(void);
	virtual BoundingBox getBoundingBox(void);
	virtual BoundingSphere getBoundingSphere(void);
	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(const glm::vec3& position);
	void setTransform(const glm::mat4& transform);

protected:
	glm::mat4 m_transform;
	BoundingBox m_boundingBox;
	BoundingSphere m_boundingSphere;
};

