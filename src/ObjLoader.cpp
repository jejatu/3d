#include "ObjLoader.h"

ObjLoader::ObjLoader(const std::string& filename) {
	std::string mtllib;
	std::vector<glm::vec3> indexedPositions;
	std::vector<glm::vec2> indexedTexcoords;
	std::vector<glm::vec3> indexedNormals;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> normals;

	std::ifstream input(filename, std::ios::in);
	std::string block;
	while (input) {
		input >> block;
		if (block == "v") {
			glm::vec3 pos;
			input >> pos.x; input >> pos.y; input >> pos.z;
			positions.push_back(pos);
		} else if (block == "vt") {
			glm::vec2 tex;
			input >> tex.x; input >> tex.y;
			texcoords.push_back(tex);
		} else if (block == "vn") {
			glm::vec3 norm;
			input >> norm.x; input >> norm.y; input >> norm.z;
			normals.push_back(norm);
		} else if (block == "f") {
			input.ignore(1);
			std::string line;
			std::getline(input, line);
			if (line.size() > 0) {
				std::vector<std::string> facePoints = split(line, ' ');
				if (facePoints.size() >= 3) {
					for (unsigned int i = 0; i < 3; ++i) {
						std::vector<std::string> pointIndices = split(facePoints[i], '/');
						int posIndex = atoi(pointIndices[0].c_str()) - 1;
						indexedPositions.push_back(positions[posIndex]);
						if (pointIndices.size() > 1) {
							int texIndex = atoi(pointIndices[1].c_str()) - 1;
							indexedTexcoords.push_back(texcoords[texIndex]);
						} else {
							indexedTexcoords.push_back(glm::vec2(0, 0));
						}
						if (pointIndices.size() > 2) {
							int normIndex = atoi(pointIndices[2].c_str()) - 1;
							indexedNormals.push_back(normals[normIndex]);
						}
						indices.push_back(indexedPositions.size() - 1);
					}
				}
				if (facePoints.size() == 4) {
					unsigned int i = 0;
					for (unsigned int j = 0; j < 3; ++j) {
						if (j == 1) i = 2;
						if (j == 2) i = 3;
						std::vector<std::string> pointIndices = split(facePoints[i], '/');
						int posIndex = atoi(pointIndices[0].c_str()) - 1;
						indexedPositions.push_back(positions[posIndex]);
						if (pointIndices.size() > 1) {
							int texIndex = atoi(pointIndices[1].c_str()) - 1;
							indexedTexcoords.push_back(texcoords[texIndex]);
						} else {
							indexedTexcoords.push_back(glm::vec2(0, 0));
						}
						if (pointIndices.size() > 2) {
							int normIndex = atoi(pointIndices[2].c_str()) - 1;
							indexedNormals.push_back(normals[normIndex]);
						}
						indices.push_back(indexedPositions.size() - 1);
					}
				}
			}
		} else if (block == "o") {
			if (indexedPositions.size() > 0) {
				ObjObject object;
				object.positions = indexedPositions;
				object.texcoords = indexedTexcoords;
				object.normals = indexedNormals;
				object.indices = indices;
				objects.push_back(object);
				indexedPositions.clear();
				indexedTexcoords.clear();
				indexedNormals.clear();
				indices.clear();
			}
		} else if (block == "usemtl") {
			input >> block;
		} else if (block == "mtllib") {
			input >> mtllib;
		}
	}
	if (indexedPositions.size() > 0) {
		ObjObject object;
		object.positions = indexedPositions;
		object.texcoords = indexedTexcoords;
		object.normals = indexedNormals;
		object.indices = indices;
		objects.push_back(object);
		indexedPositions.clear();
		indexedTexcoords.clear();
		indexedNormals.clear();
		indices.clear();
	}
} 

ObjLoader::~ObjLoader(void) {

}

std::vector<std::string> &ObjLoader::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	//function from http://stackoverflow.com/questions/236129/splitting-a-string-in-c
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> ObjLoader::split(const std::string &s, char delim) {
	//function from http://stackoverflow.com/questions/236129/splitting-a-string-in-c
    std::vector<std::string> elems;
    return split(s, delim, elems);
}