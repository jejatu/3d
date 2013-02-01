#version 130
in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec2 fragTexcoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
	fragTexcoord = texcoord;

	vec4 vertex = viewMatrix * modelMatrix * vec4(position, 1.0);

	gl_Position = projectionMatrix * vertex;
}