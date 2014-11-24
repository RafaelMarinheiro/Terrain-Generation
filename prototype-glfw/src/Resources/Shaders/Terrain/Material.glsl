vec3 colorForPosition(float h){
	if(h > 0.8){
		return vec3(0.22, 0.19, 0.2);
	} else if(h > 0.6){
		return vec3(0.77, 0.57, 0.44);
	} else if(h > 0.4){
		return vec3(0.48, 0.56, 0.32);
	} else{
		h = (h)/0.4;
		return vec3((1-h)*0.61 + h*0.48,
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
		wNormal = normalize(normal);
		albedo = colorForPosition(height);
		material = vec3(1.0, 0.0, 0.0);
	}
#endif