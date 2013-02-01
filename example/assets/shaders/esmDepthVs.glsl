#version 130
in vec3 position;

out vec4 fragVertex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
	vec4 vertex = viewMatrix * modelMatrix * vec4(position, 1.0);

	gl_Position = projectionMatrix * vertex;
	fragVertex = gl_Position;
}