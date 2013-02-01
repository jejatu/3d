#pragma once
#include <vector>
#include "Object3d.h"
#include "ShaderProgram.h"
#include "BoundingBox.h"

class Camera : public Object3d {
public:
	Camera(void);
	~Camera(void);
	void initPerspective(float fov, float aspect, float near, float far);
	void initOrtho(float left, float right, float bottom, float top, float near, float far);
	void bindMatrices(ShaderProgram* shader, const std::string& viewProjUniform);
	void bindMatrices(ShaderProgram* shader, const std::string& projUniform, const std::string& viewUniform);
	void lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);
	std::vector<glm::vec3> getFrustumCorners(void);
	glm::vec3 getPosition(void);
	glm::vec3 getForward(void);
	glm::vec3 getUp(void);
	glm::vec3 getRight(void);
	glm::mat4 getProjection(void);
	float getNear(void);
	float getFar(void);
	float getFov(void);
	float getAspectRatio(void);
	virtual BoundingBox getBoundingBox(void);
	void setProjection(const glm::mat4& projection);
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& position);

protected:
	void calculateFrustumCorners(void);

	glm::mat4 m_projection;
	float m_near;
	float m_far;
	float m_fov;
	float m_aspect;
	std::vector<glm::vec3> m_frustumCorners;
};

