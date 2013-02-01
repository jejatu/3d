#pragma once
#include "Object3d.h"
#include "ShaderProgram.h"

namespace LightTypes {
	enum LightType {
		NoLight,
		DirectionalLight,
		PointLight,
		SpotLight
	};
};

namespace DirectionalShadowMethods {
	enum DirectionalShadowMethod {
		Basic,
		Near,
		Cascaded
	};
};

namespace Shadows {
	enum Shadow {
		None,
		Basic,
		PCF,
		VSM,
		ESM
	};
};

class Light : public Object3d {
public:
	Light(void);
	~Light(void);
	virtual void bind(ShaderProgram *shader);
	LightTypes::LightType getType(void);
	BoundingBox getBoundingBox(void);
	BoundingSphere getBoundingSphere(void);

	glm::vec3 color;
	float ambient;
	float diffuse;
	float specular;
	float radius;
	Shadows::Shadow shadow;

protected:
	void bindProperties(ShaderProgram *shader);

	LightTypes::LightType m_type;
};

