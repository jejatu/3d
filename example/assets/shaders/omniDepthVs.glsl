#version 130
in vec3 position;

out vec4 eye;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
	vec4 vertex = viewMatrix * modelMatrix * vec4(position, 1.0);
	eye = -vertex;

	gl_Position = projectionMatrix * vertex;
}