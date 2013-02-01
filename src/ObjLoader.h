#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include <sstream>

class ObjObject {
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
};

class ObjLoader
{
public:
	ObjLoader(const std::string& filename);
	~ObjLoader(void);

	std::vector<ObjObject> objects;

private:
	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
};

