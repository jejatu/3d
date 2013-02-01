#pragma once
#include "Material.h"

class TextureMaterial : public Material {
public:
	TextureMaterial(void);
	~TextureMaterial(void);
	void init(std::string colorMapFilename);
	void init(std::string colorMapFilename, std::string normalMapFilename);
	void init(std::string colorMapFilename, std::string normalMapFilename, std::string specularMapFilename);
	void createBuffers(void);
	void deleteBuffers(void);
	void bind(ShaderProgram *shader);
	void unbind();

private:
	void createColorMap(std::string filename);
	void createNormalMap(std::string filename);
	void createSpecularMap(std::string filename);
};

