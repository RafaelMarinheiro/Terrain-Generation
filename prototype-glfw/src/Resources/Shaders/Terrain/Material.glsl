vec3 colorForPosition(float h, vec2 pos){
	float noise = 0.15*snoise(3*pos.yx) + 0.85;
	if(h > 0.8){
		return vec3(255/255.0, 250/255.0, 250/255.0) + 0.5;
	} else if(h > 0.6){
		return vec3(0.77, 0.57, 0.44)+0.1*noise;
	} else if(h > 0.36){
		return 0.1*(0.15*snoise(7*pos.yx) + 0.85)+vec3(0.48, 0.56, 0.32);
	} else{
		h = (h)/0.36;
		return 0.1*noise+vec3((1-h)*0.61 + h*0.48,
				  (1-h)*0.65 + h*0.56,
				  (1-h)*0.46 + h*0.32);
	}
}


#ifdef _VERTEX_
	in vec2 position;

	out float height;
	out vec3 normal;
	out vec3 daposition;

	void main(){
		height = getTerrainHeight(position);
		normal = getTerrainNormal(position);
		vec4 modelSpace = vec4(position.x, height*terrain_height, position.y, 1.0);
		vec4 worldSpace = modelMatrix * modelSpace;
		vec4 cameraSpace = viewMatrix * worldSpace;
		gl_Position = projectionMatrix * cameraSpace;

		daposition = worldSpace.xyz;
	}
#endif

#ifdef _FRAGMENT_
	in float height;
	in vec3 normal;
	in vec3 daposition;

	layout(location = 0) out vec3 wPosition;
	layout(location = 1) out vec3 wNormal;
	layout(location = 2) out vec3 albedo;
	layout(location = 3) out vec3 material;

	void main(){
		wPosition = daposition;
		wNormal = normalize(normalize(normal)+0.3*vec3(snoise(3*wPosition.xz), 0.0, snoise(3*wPosition.zx)));
		albedo = colorForPosition(height+0.05*snoise(wPosition.xz), wPosition.xz);
		material = vec3(0.1, 1.0, 0.95);
	}
#endif