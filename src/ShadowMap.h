#pragma once
#include "BaseShadowMap.h"

class ShadowMap : public BaseShadowMap {
public:
	ShadowMap(void);
	~ShadowMap(void);
	void init(int width, int height);
	void bindTexture(ShaderProgram *shader, int textureIndex, const std::string& uniformName);
	void unbindTexture(void);

};

