#pragma once
#include <glm/glm.hpp>

class BoundingBox;

class BoundingSphere {
public:
	BoundingSphere(void);
	BoundingSphere(const glm::vec3& centerVector, float radiusValue);
	~BoundingSphere(void);
	bool intersect(BoundingSphere& boundingSphere);
	bool intersect(BoundingBox& boundingBox);

	glm::vec3 center;
	float radius;
};

