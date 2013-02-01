#include <iostream>
#include "Stage.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "CubeGeometry.h"
#include "ColorMaterial.h"
#include "Mesh.h"
#include "Model.h"
#include "TextureMaterial.h"

Stage stage;

Camera camera;

DirectionalLight sun;

CubeGeometry groundGeometry;
TextureMaterial groundMaterial;
Mesh ground;

CubeGeometry cubeGeometry;
ColorMaterial cubeMaterial;
Mesh cube;

Model carModel;
TextureMaterial carMaterial;
Mesh carChassis;
Mesh carWheel[4];

void init(void);
void update(float delta);

int main(int argc, char **argv) {
	init();
	stage.run(); // start the internal loop
	stage.dispose();

	return 0;
}

void init(void) {
	// create a 960x480 window with 60 framerate, no antialias and no fullscreen
	stage.init(960, 480, 60, 0, false);
	stage.setUpdateCallback(update); // internal loop callbacks this function every frame

	camera.initPerspective(80, 960.0f / 480.0f, 0.1f, 20.0f);
	camera.lookAt(glm::vec3(4, 4, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	stage.add(&camera); // add a camera pointer to the scene

	sun.setDirection(-0.3f, -1.0f, 0.3f);
	sun.shadow = Shadows::PCF; // Percentage closer filtering shadows
	sun.ambient = 0.5f;
	sun.diffuse = 0.5f;
	sun.specular = 0.5f;
	stage.add(&sun);

	// init a 10x1x10 cube as a ground with a sand texture
	groundGeometry.init(10, 1, 10);
	groundMaterial.init("assets/sand_color.tga", "assets/sand_normal.tga");
	ground.init(&groundGeometry, &groundMaterial);
	ground.setPosition(0, -1, 0);
	stage.add(&ground);

	// init geometry as a 1x1x1 cube and init material as red color
	cubeGeometry.init(1, 1, 1);
	cubeMaterial.init(1, 0, 0);
	cube.init(&cubeGeometry, &cubeMaterial);
	stage.add(&cube);

	// load car model and texture
	carModel.init("assets/car.obj");
	carMaterial.init("assets/car.tga");

	// car model is too small for the scene so scale it by 10
	for (unsigned int i = 0; i < carModel.getChildCount(); ++i) {
		carModel.getGeometry(i).scale(10.0f);
	}
	
	// first four objects in the obj file are the wheels
	// last and the fifth object is the chassis
	carChassis.init(&carModel.getGeometry(4), &carMaterial);
	carChassis.setPosition(0, 0.25f, 2.5f);
	stage.add(&carChassis);
	for (int i = 0; i < 4; ++i) {
		carWheel[i].init(&carModel.getGeometry(i), &carMaterial);
		stage.add(&carWheel[i]);
	}

	// put the wheels in the right places
	glm::vec3 chassisPos = carChassis.getPosition();
	carWheel[0].setPosition(chassisPos.x + 0.5f, chassisPos.y - 0.25f, chassisPos.z - 1.0f);
	carWheel[1].setPosition(chassisPos.x - 0.5f, chassisPos.y - 0.25f, chassisPos.z - 1.0f);
	carWheel[2].setPosition(chassisPos.x + 0.5f, chassisPos.y - 0.25f, chassisPos.z + 1.0f);
	carWheel[3].setPosition(chassisPos.x - 0.5f, chassisPos.y - 0.25f, chassisPos.z + 1.0f);
}

void update(float delta) {
	camera.rotate(glm::vec3(0, 1, 0), 60 * delta);
}