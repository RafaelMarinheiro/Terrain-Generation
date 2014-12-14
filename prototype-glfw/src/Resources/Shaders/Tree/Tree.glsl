#ifdef _VERTEX_
	in vec3 position;
	in vec3 normal;
	
	out vec3 daposition;
	out vec3 norml;
	void main(){
		
		vec4 modelSpace = vec4(position.x, position.y, position.z, 1.0);
		vec4 modelNorm = vec4(normal.x,normal.y,normal.z,0.0);
		vec4 worldSpace = modelMatrix * modelSpace;
		vec4 cameraSpace = viewMatrix * worldSpace;
		mat4 normMat = transpose(inverse(modelMatrix));		
		gl_Position = projectionMatrix * cameraSpace;
		norml = (normMat*modelNorm).xyz;
		daposition = worldSpace.xyz;
	}
#endif

#ifdef _FRAGMENT_
	
	in vec3 daposition;
	in vec3 norml;

	layout(location = 0) out vec3 wPosition;
	layout(location = 1) out vec3 wNormal;
	layout(location = 2) out vec3 albedo;
	layout(location = 3) out vec3 material;

	void main(){
		wPosition = daposition;
		wNormal = normalize(norml);
		albedo = vec3(0.5,0.25,0.0625);
		material = vec3(1.0, 1.0, 0.0);
	}
#endif