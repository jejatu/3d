#include "CubeGeometry.h"

CubeGeometry::CubeGeometry(void) {

}

CubeGeometry::~CubeGeometry(void) {

}

void CubeGeometry::init(float width, float height, float depth) {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;
	positions.push_back(glm::vec3(width/2, -height/2, -depth/2));
	positions.push_back(glm::vec3(-width/2, -height/2, -depth/2));
	positions.push_back(glm::vec3(-width/2, height/2, -depth/2));
	positions.push_back(glm::vec3(width/2, height/2, -depth/2));
	positions.push_back(glm::vec3(-width/2, -height/2, depth/2));
	positions.push_back(glm::vec3(width/2, -height/2, depth/2));
	positions.push_back(glm::vec3(width/2, height/2, depth/2));
	positions.push_back(glm::vec3(-width/2, height/2, depth/2));
	positions.push_back(glm::vec3(-width/2, -height/2, -depth/2));
	positions.push_back(glm::vec3(-width/2, -height/2, depth/2));
	positions.push_back(glm::vec3(-width/2, height/2, depth/2));
	positions.push_back(glm::vec3(-width/2, height/2, -depth/2));
	positions.push_back(glm::vec3(width/2, -height/2, depth/2));
	positions.push_back(glm::vec3(width/2, -height/2, -depth/2));
	positions.push_back(glm::vec3(width/2, height/2, -depth/2));
	positions.push_back(glm::vec3(width/2, height/2, depth/2));
	positions.push_back(glm::vec3(-width/2, -height/2, -depth/2));
	positions.push_back(glm::vec3(width/2, -height/2, -depth/2));
	positions.push_back(glm::vec3(width/2, -height/2, depth/2));
	positions.push_back(glm::vec3(-width/2, -height/2, depth/2));
	positions.push_back(glm::vec3(width/2, height/2, -depth/2));
	positions.push_back(glm::vec3(-width/2, height/2, -depth/2));
	positions.push_back(glm::vec3(-width/2, height/2, depth/2));
	positions.push_back(glm::vec3(width/2, height/2, depth/2));

	texcoords.push_back(glm::vec2(0, 0));
	texcoords.push_back(glm::vec2(1, 0));
	texcoords.push_back(glm::vec2(1, 1));
	texcoords.push_back(glm::vec2(0, 1));
	texcoords.push_back(glm::vec2(0, 0));
	texcoords.push_back(glm::vec2(1, 0));
	texcoords.push_back(glm::vec2(1, 1));
	texcoords.push_back(glm::vec2(0, 1));
	texcoords.push_back(glm::vec2(0, 0));
	texcoords.push_back(glm::vec2(1, 0));
	texcoords.push_back(glm::vec2(1, 1));
	texcoords.push_back(glm::vec2(0, 1));
	texcoords.push_back(glm::vec2(0, 0));
	texcoords.push_back(glm::vec2(1, 0));
	texcoords.push_back(glm::vec2(1, 1));
	texcoords.push_back(glm::vec2(0, 1));
	texcoords.push_back(glm::vec2(0, 0));
	texcoords.push_back(glm::vec2(1, 0));
	texcoords.push_back(glm::vec2(1, 1));
	texcoords.push_back(glm::vec2(0, 1));
	texcoords.push_back(glm::vec2(0, 0));
	texcoords.push_back(glm::vec2(1, 0));
	texcoords.push_back(glm::vec2(1, 1));
	texcoords.push_back(glm::vec2(0, 1));

	unsigned int i[] = {0, 1, 2,
						0, 2, 3,
						4, 5, 6,
						4, 6, 7,
						8, 9, 10,
						8, 10, 11,
						12, 13, 14,
						12, 14, 15,
						16, 17, 18,
						16, 18, 19,
						20, 21, 22,
						20, 22, 23};
	
	std::vector<unsigned int> indices(&i[0], &i[0]+36);

	initVertices(positions, texcoords, indices);
}