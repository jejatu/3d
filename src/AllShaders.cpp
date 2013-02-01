#include "AllShaders.h"

AllShaders::AllShaders(void) {
	
}

AllShaders::~AllShaders(void) {

}

void AllShaders::init(void) {
	noLight.addShader(Shader(GL_VERTEX_SHADER, ShaderBuilder::load("assets/shaders/noLightVs.glsl")));
	noLight.addShader(Shader(GL_FRAGMENT_SHADER, ShaderBuilder::load("assets/shaders/noLightFs.glsl")));
	noLight.createProgram();

	vsmDepth.addShader(Shader(GL_VERTEX_SHADER, ShaderBuilder::load("assets/shaders/vsmDepthVs.glsl")));
	vsmDepth.addShader(Shader(GL_FRAGMENT_SHADER, ShaderBuilder::load("assets/shaders/vsmDepthFs.glsl")));
	vsmDepth.createProgram();

	omniDepth.addShader(Shader(GL_VERTEX_SHADER, ShaderBuilder::load("assets/shaders/omniDepthVs.glsl")));
	omniDepth.addShader(Shader(GL_FRAGMENT_SHADER, ShaderBuilder::load("assets/shaders/omniDepthFs.glsl")));
	omniDepth.createProgram();

	esmDepth.addShader(Shader(GL_VERTEX_SHADER, ShaderBuilder::load("assets/shaders/esmDepthVs.glsl")));
	esmDepth.addShader(Shader(GL_FRAGMENT_SHADER, ShaderBuilder::load("assets/shaders/esmDepthFs.glsl")));
	esmDepth.createProgram();
	
	Shader dirLightVertexShader(GL_VERTEX_SHADER, ShaderBuilder::load("assets/shaders/dirLightVs.glsl"));
	
	dirNoShadow.addShader(dirLightVertexShader);
	dirNoShadow.addShader(Shader(GL_FRAGMENT_SHADER,
					ShaderBuilder::merge("assets/shaders/dirLightFs.glsl", "assets/shaders/noShadow_snippet.glsl")));
	dirNoShadow.createProgram();

	dirBasic.addShader(dirLightVertexShader);
	dirBasic.addShader(Shader(GL_FRAGMENT_SHADER,
					  ShaderBuilder::merge("assets/shaders/dirLightFs.glsl", "assets/shaders/dirBasic_snippet.glsl")));
	dirBasic.createProgram();

	dirPcf.addShader(dirLightVertexShader);
	dirPcf.addShader(Shader(GL_FRAGMENT_SHADER,
					  ShaderBuilder::merge("assets/shaders/dirLightFs.glsl", "assets/shaders/dirPcf_snippet.glsl")));
	dirPcf.createProgram();

	dirVsm.addShader(dirLightVertexShader);
	dirVsm.addShader(Shader(GL_FRAGMENT_SHADER,
					  ShaderBuilder::merge("assets/shaders/dirLightFs.glsl", "assets/shaders/dirVsm_snippet.glsl")));
	dirVsm.createProgram();
	
	dirEsm.addShader(dirLightVertexShader);
	dirEsm.addShader(Shader(GL_FRAGMENT_SHADER,
					  ShaderBuilder::merge("assets/shaders/dirLightFs.glsl", "assets/shaders/dirEsm_snippet.glsl")));
	dirEsm.createProgram();

	Shader pointLightVertexShader(GL_VERTEX_SHADER, ShaderBuilder::load("assets/shaders/pointLightVs.glsl"));

	omniNoShadow.addShader(pointLightVertexShader);
	omniNoShadow.addShader(Shader(GL_FRAGMENT_SHADER, 
					 ShaderBuilder::merge("assets/shaders/pointLightFs.glsl", "assets/shaders/noShadow_snippet.glsl")));
	omniNoShadow.createProgram();

	omniBasic.addShader(pointLightVertexShader);
	omniBasic.addShader(Shader(GL_FRAGMENT_SHADER, 
					   ShaderBuilder::merge("assets/shaders/pointLightFs.glsl", "assets/shaders/omniBasic_snippet.glsl")));
	omniBasic.createProgram();

	omniPcf.addShader(pointLightVertexShader);
	omniPcf.addShader(Shader(GL_FRAGMENT_SHADER,
					   ShaderBuilder::merge("assets/shaders/pointLightFs.glsl", "assets/shaders/omniPcf_snippet.glsl")));
	omniPcf.createProgram();
}