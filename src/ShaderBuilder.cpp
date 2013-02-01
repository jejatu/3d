#include "ShaderBuilder.h"

std::string ShaderBuilder::merge(const std::string& shader, const std::string& addon) {
	std::string baseShader = load(shader);
	std::string addonShader = load(addon);
	int main = baseShader.find("void main()");
	if (main != std::string::npos) {
		baseShader.insert(main, "\n");
		baseShader.insert(main, addonShader);
	}
	return baseShader;
}

std::string ShaderBuilder::load(const std::string& filename) {
    // reads file as text
    // getline seems like a bad way to do it
    std::string output = "";
    std::ifstream input;
    input.open(filename);
    if (!input.fail()) {
        while (input) {
            std::string line;
            std::getline(input, line);
            output.append(line + "\n");
        }
    }
    input.close();
    input.clear();
    return output;
}