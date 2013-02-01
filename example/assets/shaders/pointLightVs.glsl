#version 130
in vec3 position;
in vec2 texcoord;
in vec3 normal;
in vec3 tangent;

out vec3 fragNormal;
out vec2 fragTexcoord;
out vec4 fragLightDir;
out vec3 eye;
out vec4 distance;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform bool bumpMapping;

void main() {
	fragNormal = normalMatrix * normal;
	fragTexcoord = texcoord;

	vec4 vertex = viewMatrix * modelMatrix * vec4(position, 1.0);

	vec3 n = normalize(normalMatrix * normal);
	vec3 t = normalize(normalMatrix * tangent);
	vec3 b = cross(n, t);

	vec4 tempVec = viewMatrix * vec4(lightPos, 1) - vertex;
	if (bumpMapping) {
		fragLightDir.x = dot(tempVec.xyz, t);
		fragLightDir.y = dot(tempVec.xyz, b);
		fragLightDir.z = dot(tempVec.xyz, n);
		fragLightDir.w = 0;
	} else {
		fragLightDir = tempVec;
	}

	tempVec = -vertex;
	if (bumpMapping) {
		eye.x = dot(tempVec.xyz, t);
		eye.y = dot(tempVec.xyz, b);
		eye.z = dot(tempVec.xyz, n);
	} else {
		eye = tempVec.xyz;
	}

	distance = vec4(lightPos, 1) - modelMatrix * vec4(position, 1.0);
	
	gl_Position = projectionMatrix * vertex;
}