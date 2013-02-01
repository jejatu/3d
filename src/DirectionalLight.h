#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight(void);
	~DirectionalLight(void);
	void bind(ShaderProgram* shader);
	void setDirection(float x, float y, float z);
	void setDirection(const glm::vec3& direction);
	glm::vec3 getPosition(void);
	glm::vec3 getForward(void);
	glm::vec3 getUp(void);
	glm::vec3 getRight(void);
	void setShadowMethod(DirectionalShadowMethods::DirectionalShadowMethod shadowMethod, float shadowMethodValue = 0);
	DirectionalShadowMethods::DirectionalShadowMethod getShadowMethod(void);
	float getShadowMethodValue(void);

private:
	DirectionalShadowMethods::DirectionalShadowMethod m_shadowMethod;
	float m_shadowMethodValue;
};
