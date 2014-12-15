uniform vec3 lightDirection;

#ifdef _VERTEX_
	in vec2 position;
	out vec2 texCoord;

	void main(){
		gl_Position = vec4(position, 0.0, 1.0);
		texCoord = position*vec2(0.5,0.5) + vec2(0.5, 0.5);
	}
#endif

#ifdef _FRAGMENT_

	in vec2 texCoord;

	uniform sampler2D gPositionMap;
	uniform sampler2D gNormalMap;
	uniform sampler2D gAlbedoMap;
	uniform sampler2D gMaterialMap;
	uniform vec3 eyePosition;



	out vec4 outColor;

	void main(){

		// gl_FragCoordivec2 size = textureSize(depthtex, 0);
		vec3 position = texture(gPositionMap, texCoord).xyz;
		vec3 normal = texture(gNormalMap, texCoord).xyz;
		vec3 albedo = texture(gAlbedoMap, texCoord).xyz;
		vec3 material = texture(gMaterialMap, texCoord).xyz;

		vec3 viewDirection = normalize((viewMatrix * vec4(position, 1.0)).xyz);

		float lightIntensity = DiffuseLighting(lightDirection, viewDirection, normal, material.x);

		vec3 rec = reflect(normal, viewDirection);
		// scattered sunlight between two points
		// camera=observer
		// point=point on the ground
		// sundir=unit vector towards the sun
		// return scattered light and extinction coefficient
		// vec3 extinction;
		// vec3 inscatter = inScattering(eyePosition.xzy, position.xzy, vec3(0.0, 0.0, 1.0), extinction);
		outColor = 2*lightIntensity*vec4(albedo, 1.0)*(material.z);
		outColor += material.x*texture(skyTexture, directionToCoordinate(rec));
		// outColor = vec4(albedo, 1.0);
		// outColor.xyz = extinction;
	}

#endif