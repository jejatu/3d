#version 130
in vec4 fragVertex;

out vec4 fragColor;

void main() {
	float depth = fragVertex.z / fragVertex.w;
	depth = depth * 0.5 + 0.5;
	fragColor = vec4(depth, 0, 0, 0);
}