float getShadowValue() {
	vec4 shadowCoord = projCoord / projCoord.w;
	if (shadowCoord.x < 0 || shadowCoord.x > 1 || shadowCoord.y < 0 || shadowCoord.y > 1) return 0.0;
	float occluder = texture(shadowMap, shadowCoord.xy).r;
	if (bothSides == false) {
		if (occluder >= shadowCoord.z) return 1.0;
		if (occluder > 0) return 0.0;
		return 1.0;
	} else {
		if (occluder >= shadowCoord.z - 0.001) return 1.0;
	}
	return 0.0;
}