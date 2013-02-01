#version 130

in vec3 fragNormal;
in vec2 fragTexcoord;
in vec4 fragLightDir;
in vec3 eye;
in vec4 projCoord;

out vec4 fragColor;

uniform vec3 color;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D shadowMap;
uniform vec2 pixelOffset;
uniform bool bumpMapping;
uniform bool bothSides;

void main() {
	vec4 materialColor = vec4(color, 1) + texture(colorMap, fragTexcoord);
	materialColor.w = 1.0;
	vec3 N = normalize(fragNormal);
	if (bumpMapping) {
		N = normalize(texture(normalMap, fragTexcoord).xyz * 2.0 - 1.0);
	}
	vec4 finalColor = vec4(ambient, 1) * materialColor;
	vec3 L = normalize(fragLightDir.xyz);
	float lambertTerm = dot(N, L);
	if (lambertTerm > 0.0) {
		float shadow = getShadowValue();
		if (shadow > 0.0) {
			finalColor += vec4(diffuse, 1) * shadow * materialColor * lambertTerm;
			vec3 E = normalize(eye);
			vec3 R = reflect(-L, N);
			float spec = pow(max(dot(R, E), 0.0), 50);
			finalColor += vec4(specular, 1) * shadow * materialColor * spec;
		}
	}

	fragColor = finalColor;
}