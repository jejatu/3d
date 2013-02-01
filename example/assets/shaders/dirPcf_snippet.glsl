float getShadow(vec4 shadowCoord, float x, float y) {
	float occluder = texture(shadowMap, shadowCoord.xy + vec2(x, y)).r;
	if (bothSides == false) {
		if (occluder >= shadowCoord.z) return 1.0;
		if (occluder > 0) return 0.0;
		return 1.0;
	} else {
		if (occluder >= shadowCoord.z - 0.001) return 1.0;
	}
	return 0.0;
}

float getShadowValue() {
	vec4 shadowCoord = projCoord / projCoord.w;
	if (shadowCoord.x < 0 || shadowCoord.x > 1 || shadowCoord.y < 0 || shadowCoord.y > 1) return 0.0;
	float shadow = 0.0;
	int times = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			shadow += getShadow(shadowCoord, i * pixelOffset.x * 0.5f, j * pixelOffset.y * 0.5f);
			times++;
		}
	}
	shadow /= times;
	return shadow;
}