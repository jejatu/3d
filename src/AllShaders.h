#pragma once
#include "ShaderBuilder.h"
#include "ShaderProgram.h"

class AllShaders {
public:
	AllShaders(void);
	~AllShaders(void);
	void init(void);
	
	ShaderProgram noLight;
	ShaderProgram esmDepth;
	ShaderProgram vsmDepth;
	ShaderProgram omniDepth;
	ShaderProgram dirNoShadow;
	ShaderProgram dirBasic;
	ShaderProgram dirPcf;
	ShaderProgram dirVsm;
	ShaderProgram dirEsm;
	ShaderProgram omniNoShadow;
	ShaderProgram omniBasic;
	ShaderProgram omniPcf;
};

