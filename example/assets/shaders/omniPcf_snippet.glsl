float lookup(float distance2, float x, float y, float z) {
	float sample = texture(shadowMap, -distance.xyz + vec3(x, y, z)).r;
	if (bothSides == false) {
		if (sample > distance2 + 1) return 1.0;
		if (sample > 0) return 0.0;
		return 1.0;
	} else {
		if (sample > distance2) return 1.0;
	}
	return 0.0;
}

float getShadowValue() {
	float distance2 = dot(distance, distance);
	float shadow = 0.0;
	int times = 0;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			for (int g = -1; g < 2; ++g) {
				shadow += lookup(distance2, i * 0.05, j * 0.05, g * 0.05);
				times++;
			}
		}
	}
	shadow /= times;
	return shadow;
}