#pragma once
#include <string>
#include <fstream>
#include "ShaderProgram.h"
class ShaderBuilder {
public:
	static std::string load(const std::string& filename);
	static std::string merge(const std::string& shader, const std::string& addon);

};

