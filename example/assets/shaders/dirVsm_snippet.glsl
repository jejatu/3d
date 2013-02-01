float getShadowValue() {
	vec4 shadowCoord = projCoord / projCoord.w;
	vec2 moments = texture(shadowMap, shadowCoord.xy).rg;
	if (shadowCoord.z <= moments.x) return 1.0;
	float variance = moments.y - (moments.x * moments.x);
	variance = max(variance, 0.000002);
	float d = shadowCoord.z - moments.x;
	float p_max = variance / (variance + d*d);
	return p_max;
}