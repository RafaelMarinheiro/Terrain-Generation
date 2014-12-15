
uniform sampler2D skyTexture;

vec3 inverseStereographicProjection(vec2 u){
	float l = dot(u, u);
	if(l > 1.0){
		u = u/l;
		l = 1.0/l;
	}

	return vec3(2.0 * u, 1.0 - l) / (1.0 + l);
}

vec2 stereographicProjection(vec3 r){
	return vec2(r.x, r.z)/(1+r.y);
}

vec2 directionToCoordinate(vec3 r){
	vec2 u = stereographicProjection(r);
	return u*0.5 + vec2(0.5, 0.5);
}

vec2 clampStereoCoordinate(vec2 u){
	float l = dot(u, u);
	if(l > 1.0){
		u = u/l;
		l = 1.0/l;
	}
	return u;
}