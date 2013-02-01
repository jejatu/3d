#pragma once
#include <vector>
#include <memory>
#include "Mesh.h"
#include "ObjLoader.h"

class Model {
public:
	Model(void);
	Model(const std::string& filename);
	~Model(void);
	void init(const std::string& filename);
	Geometry& getGeometry(unsigned int index);
	unsigned int getChildCount(void);

private:
	std::vector<Geometry> m_geometries;
};

