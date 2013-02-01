#version 130

in vec3 fragNormal;
in vec2 fragTexcoord;
in vec4 fragLightDir;
in vec3 eye;
in vec4 distance;

out vec4 fragColor;

uniform vec3 color;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform samplerCube shadowMap;
uniform float lightRadius;
uniform bool bumpMapping;
uniform bool bothSides;

void main() {
	float attenuation = 1.0;
	if (lightRadius > 0) {
		float kc = 1.0; //constant attenuation factor
		float kl = 2.0 / lightRadius; //linear attenuation factor
		float kq = 1.0 / (lightRadius * lightRadius); //quadratic attenuation factor
		float d = length(fragLightDir.xyz);
		attenuation = 1.0 / (kc + kl * d + kq * d * d);
	}

	vec4 materialColor = vec4(color, 1) + texture(colorMap, fragTexcoord);
	vec4 finalColor = vec4(ambient, 1) * materialColor * attenuation;
	vec3 N = normalize(fragNormal);
	if (bumpMapping) {
		N = normalize(texture(normalMap, fragTexcoord).xyz * 2.0 - 1.0);
	}
	vec3 L = normalize(fragLightDir.xyz);
	float lambertTerm = dot(N, L);
	if (lambertTerm > 0.0) {
		float shadow = getShadowValue();

		if (shadow > 0.0) {
			finalColor += vec4(diffuse, 1) * shadow * materialColor * lambertTerm;
			vec3 E = normalize(eye);
			vec3 R = reflect(-L, N);
			float spec = pow(max(dot(R, E), 0.0), 50);
			finalColor += vec4(specular, 1) * shadow * spec;
		}
	}

	fragColor = finalColor;
}