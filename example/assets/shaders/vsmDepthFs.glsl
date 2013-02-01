#version 130
in vec4 fragVertex;

out vec4 fragColor;

void main() {
	float depth = fragVertex.z / fragVertex.w;
	depth = depth * 0.5 + 0.5;
	float moment1 = depth;
	float moment2 = depth * depth;
	float dx = dFdx(depth);
	float dy = dFdy(depth);
	moment2 += 0.25 * (dx*dx + dy*dy);

	fragColor = vec4(moment1, moment2, 0, 0);
}