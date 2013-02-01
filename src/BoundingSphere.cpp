#include "BoundingSphere.h"
#include "BoundingBox.h"

BoundingSphere::BoundingSphere(void) {
	radius = 0;
}

BoundingSphere::BoundingSphere(const glm::vec3& centerVector, float radiusValue) {
	center = centerVector;
	radius = radiusValue;
}

BoundingSphere::~BoundingSphere(void) {

}

bool BoundingSphere::intersect(BoundingSphere& boundingSphere) {
	return (radius + boundingSphere.radius) > glm::length(center - boundingSphere.center);
}

bool BoundingSphere::intersect(BoundingBox& boundingBox) {
	glm::vec3 closestPoint;
	float a = 0;
	float b = 0;
	a = center.x;
	b = boundingBox.min.x;
	if (a < b) a = b;
	b = boundingBox.max.x;
	if (a > b) a = b;
	closestPoint.x = a;

	a = center.y;
	b = boundingBox.min.y;
	if (a < b) a = b;
	b = boundingBox.max.y;
	if (a > b) a = b;
	closestPoint.y = a;

	a = center.z;
	b = boundingBox.min.z;
	if (a < b) a = b;
	b = boundingBox.max.z;
	if (a > b) a = b;
	closestPoint.z = a;

	glm::vec3 distance = closestPoint - center;

	return glm::dot(distance, distance) <= radius * radius;
}