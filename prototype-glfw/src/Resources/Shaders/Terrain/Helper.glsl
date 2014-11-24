uniform sampler2D terrain_heightMap;
uniform float terrain_size;
uniform float terrain_height;

float getTerrainHeight(vec2 position){
	// vec2 cord = position/terrain_size;
	// cord = cord-vec2(0.5, 0.5);
	// return (1-cord.x*cord.x-cord.y*cord.y);
	vec4 height = texture(terrain_heightMap, position/terrain_size);
	return height.r;
}

vec3 getTerrainNormal(vec2 position){
	const ivec3 off = ivec3(-1,0,1);

	vec2 cord = position/terrain_size;
	// cord = cord-vec2(0.5, 0.5);

	// vec3 norm = cross(vec3(1.0, -2*cord.x, 0), vec3(0.0, -2*cord.y, 1.0));

	// return norm;
	// if(dot(norm, vec3(0, 1, 0)))

	float s11 = getTerrainHeight(position);
	float s01 = textureOffset(terrain_heightMap, cord, off.xy).x;
	float s21 = textureOffset(terrain_heightMap, cord, off.zy).x;
	float s10 = textureOffset(terrain_heightMap, cord, off.yx).x;
	float s12 = textureOffset(terrain_heightMap, cord, off.yz).x;

	vec3 va = normalize(vec3(terrain_size/513, (s21-s01)*terrain_height, 0));
	vec3 vb = normalize(vec3(0, (s21-s01)*terrain_height, terrain_size/513));
	vec3 normal = cross(vb,va);

	// return vec3(0, 1, 0);
	return normal;
}