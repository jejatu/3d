float getShadowValue() {
	vec4 shadowCoord = projCoord / projCoord.w;
	float occluder = texture(shadowMap, shadowCoord.xy).r;
	float overdark = 50;
	return clamp(exp(overdark * (occluder - shadowCoord.z)), 0.0, 1.0);
}