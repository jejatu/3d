#version 130
in vec4 eye;

out vec4 fragColor;

void main() {
	fragColor = vec4(dot(eye, eye), 0, 0, 0);
}