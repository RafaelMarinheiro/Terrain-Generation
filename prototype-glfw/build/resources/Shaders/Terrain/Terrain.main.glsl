
uniform vec3 lightDirection;

vec4 colorForPosition(float h){
	if(h > 0.8){
		return vec4(0.22, 0.19, 0.2, 1.0);
	} else if(h > 0.6){
		return vec4(0.77, 0.57, 0.44, 1.0);
	} else if(h > 0.4){
		return vec4(0.48, 0.56, 0.32, 1.0);
	} else{
		h = (h)/0.4;
		return vec4((1-h)*0.61 + h*0.48,
				  (1-h)*0.65 + h*0.56,
				  (1-h)*0.46 + h*0.32, 1.0);
	}
}


#ifdef _VERTEX_
	in vec2 position;

	out float height;
	out vec3 normal;
	out vec3 viewDirection;

	void main(){
		height = getTerrainHeight(position);
		normal = getTerrainNormal(position);
		vec4 worldspace = vec4(position.x, height*terrain_height, position.y, 1.0);
		vec4 cameraSpace = viewMatrix * (modelMatrix * worldspace);
		gl_Position = projectionMatrix * cameraSpace;

		viewDirection = cameraSpace.xyz;
		normal = (modelMatrix*vec4(normal, 0.0)).xyz;
		// gl_Position = vec4(position, 0.0, 1.0);
	}
#endif

#ifdef _FRAGMENT_
	in float height;
	in vec3 normal;
	in vec3 viewDirection;
	out vec4 outColor;


	void main(){
		vec3 dnormal = normalize(normal);
		vec3 dview = normalize(viewDirection);
		float lightIntensity = DiffuseLighting(lightDirection, -dview, dnormal, 1.0);
		outColor = 2*(lightIntensity+0.2)*colorForPosition(height);
		// outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
#endif