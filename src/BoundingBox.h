#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class BoundingSphere;

class BoundingBox {
public:
	BoundingBox(void);
	BoundingBox(const glm::vec3& minVector, const glm::vec3& maxVector);
	BoundingBox(const std::vector<glm::vec3>& points);
	~BoundingBox(void);
	bool intersect(BoundingBox& boundingBox);
	bool intersect(BoundingSphere& boundingSphere);

	glm::vec3 min;
	glm::vec3 max;
};

