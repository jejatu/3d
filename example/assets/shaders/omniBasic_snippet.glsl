float getShadowValue() {
	float distance2 = dot(distance, distance);
	float sample = texture(shadowMap, -distance.xyz).r;
	if (bothSides == false) {
		if (sample > distance2 + 1) return 1.0;
		if (sample > 0) return 0.0;
		return 1.0;
	} else {
		if (sample > distance2) return 1.0;
	}
	return 0.0;
}