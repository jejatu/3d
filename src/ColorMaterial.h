#pragma once
#include "Material.h"

class ColorMaterial : public Material {
public:
	ColorMaterial(void);
	~ColorMaterial(void);
	void init(float r, float g, float b);
	void bind(ShaderProgram *shader);
	void unbind();

private:
	ShaderProgram* m_lastShader;
};

