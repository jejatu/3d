#version 130
in vec2 fragTexcoord;

out vec4 fragColor;

uniform vec3 color;
uniform sampler2D diffuseMap;

void main() {
	vec4 materialColor = vec4(color, 1) + texture2D(diffuseMap, fragTexcoord);
	vec4 finalColor = materialColor;
	fragColor = finalColor;
}