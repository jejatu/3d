#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight(void);
	~PointLight(void);
	void bind(ShaderProgram *shader);
};

