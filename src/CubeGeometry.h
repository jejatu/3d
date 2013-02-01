#pragma once
#include "Geometry.h"

class CubeGeometry : public Geometry {
public:
	CubeGeometry(void);
	~CubeGeometry(void);
	void init(float width, float height, float depth);
};

