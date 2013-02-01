#pragma once
#include <fstream>
#include "Object3d.h"
#include "ShaderProgram.h"
#include "Geometry.h"
#include "Material.h"

class Mesh : public Object3d {
public:
	Mesh(void);
	~Mesh(void);
	void init(Geometry* geometry, Material* material);
	void render(ShaderProgram* shader);

	Geometry* geometry;
	Material* material;
	bool bothSides;
};

