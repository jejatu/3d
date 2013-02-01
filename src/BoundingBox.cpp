#include "BoundingBox.h"
#include "BoundingSphere.h"

BoundingBox::BoundingBox(void) {

}

BoundingBox::BoundingBox(const glm::vec3& minVector, const glm::vec3& maxVector) {
	min = minVector;
	max = maxVector;
}

BoundingBox::BoundingBox(const std::vector<glm::vec3>& points) {
	if (points.size() > 0) {
		min = points[0];
		max = points[0];
		for (unsigned int i = 1; i < points.size(); ++i) {
			if (points[i].x < min.x) min.x = points[i].x;
			if (points[i].y < min.y) min.y = points[i].y;
			if (points[i].z < min.z) min.z = points[i].z;
			if (points[i].x > max.x) max.x = points[i].x;
			if (points[i].y > max.y) max.y = points[i].y;
			if (points[i].z > max.z) max.z = points[i].z;
		}
	}
}

BoundingBox::~BoundingBox(void) {

}

bool BoundingBox::intersect(BoundingBox& boundingBox) {
	return (min.x < boundingBox.max.x) && (max.x > boundingBox.min.x) &&
		   (min.y < boundingBox.max.y) && (max.y > boundingBox.min.y) &&
		   (min.z < boundingBox.max.z) && (max.z > boundingBox.min.z);
}

bool BoundingBox::intersect(BoundingSphere& boundingSphere) {
	return boundingSphere.intersect(*this);
}