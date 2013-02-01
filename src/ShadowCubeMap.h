#pragma once
#include "BaseShadowMap.h"

class ShadowCubeMap : public BaseShadowMap {
public:
	ShadowCubeMap(void);
	~ShadowCubeMap(void);
	void init(int width, int height);
	void bindTexture(ShaderProgram *shader, int textureIndex, const std::string& uniformName);
	void unbindTexture(void);
	void attach(GLenum target);

};

