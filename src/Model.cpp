#include "Model.h"

Model::Model(void) {

}

Model::~Model(void) {
	
}

void Model::init(const std::string& filename) {
	ObjLoader obj(filename);
	for (unsigned int i = 0; i < obj.objects.size(); ++i) {
		Geometry geometry;
		geometry.init(obj.objects[i].positions, obj.objects[i].texcoords, obj.objects[i].indices, obj.objects[i].normals);
		m_geometries.push_back(geometry);
	}
}

Geometry& Model::getGeometry(unsigned int index) {
	return m_geometries[index];
}

unsigned int Model::getChildCount(void) {
	return m_geometries.size();
}

