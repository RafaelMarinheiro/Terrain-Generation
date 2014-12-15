
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
	uniform mat4 inverseMVP;

	uniform vec3 lightDirection;
	const float pi = 3.14159;
	uniform float waterHeight;
	uniform float time;
	uniform int numWaves;
	uniform float amplitude[8];
	uniform float wavelength[8];
	uniform float speed[8];
	uniform vec2 direction[8];

	out vec4 outColor;



	float wave(int i, float x, float y) {
		float frequency = 2*pi/wavelength[i];
		float phase = speed[i] * frequency;
		float theta = dot(direction[i], vec2(x, y));
		return amplitude[i] * sin(theta * frequency + time * phase);
	}

	float waveHeight(float x, float y) {
		float height = 0.0;
		for (int i = 0; i < numWaves; ++i)
			height += wave(i, x, y);
		return height;
	}

	float dWavedx(int i, float x, float y) {
		float frequency = 2*pi/wavelength[i];
		float phase = speed[i] * frequency;
		float theta = dot(direction[i], vec2(x, y));
		float A = amplitude[i] * direction[i].x * frequency;
		return A * cos(theta * frequency + time * phase);
	}

	float dWavedy(int i, float x, float y) {
		float frequency = 2*pi/wavelength[i];
		float phase = speed[i] * frequency;
		float theta = dot(direction[i], vec2(x, y));
		float A = amplitude[i] * direction[i].y * frequency;
		return A * cos(theta * frequency + time * phase);
	}

	vec3 waveNormal(float x, float y) {
		float dx = 0.0;
		float dy = 0.0;
		for (int i = 0; i < numWaves; ++i) {
			dx += dWavedx(i, x, y);
			dy += dWavedy(i, x, y);
		}
		dx += snoise(vec2(x, y))*0.15;
		dy += snoise(vec2(y, x))*0.15;
		vec3 n = vec3(-dx, 1.0, -dy);
		return normalize(n);
	}

	float fresnelTerm(vec3 normal, vec3 eyeVec){
		float R0 = 0.5;
		float refractionStrength = 0.0;
		float angle = 1.0 - dot(normal, eyeVec);
		float fresnel = angle * angle;
		fresnel = fresnel * fresnel;
		fresnel = fresnel * angle;
		return (fresnel * (1.0 - R0) + R0 - refractionStrength);
	}

	float shininess = 0.7f;
	float specular_intensity = 0.32;
	
	vec3 sunColor = vec3(1.0f, 1.0f, 1.0f);

	void main(){
		vec3 position = texture(gPositionMap, texCoord).xyz;
		vec3 terrainColor = texture(gAlbedoMap, texCoord).xyz;
		vec3 material = texture(gMaterialMap, texCoord).xyz;
		float depthTerrain = length(eyePosition - position);
		vec2 pixel = 2.0*(texCoord-vec2(0.5, 0.5));
		vec4 pixelVector = inverseMVP*(vec4(pixel.x, pixel.y, 1.0, 1.0)); 
		vec3 eyeVector = (pixelVector.xyz/pixelVector.w) - eyePosition;
		eyeVector = normalize(eyeVector);

		if(eyeVector.y == 0){
			discard;
		} else{
			float depthWater = -(eyePosition.y - waterHeight)/eyeVector.y;

			if(depthWater > 0){
				vec3 waterPosition = eyePosition + depthWater*eyeVector;
				vec3 waterNormal = waveNormal(waterPosition.x, waterPosition.z);
				float k = -eyeVector.y;
				k = exp(-50.0*k*k);
				// k = 0;

				vec3 normal = normalize(mix(waterNormal, vec3(0.0, 1.0, 0.0), k));
				
				float fresnel = fresnelTerm(normal, eyeVector);

				vec3 direction = reflect(eyeVector, normal);
				vec3 colorWater = texture(skyTexture, directionToCoordinate(direction)).xyz*0.7;

				vec3 specular = vec3(0.0);

				
				float dotSpec = clamp(dot(direction, lightDirection), 0, 1);
				specular = (lightDirection.y) * ((pow(dotSpec, 256.0f)) * (shininess * 1.8f + 0.2f))* sunColor;
				specular += specular * 25 * (shininess - 0.05f) * sunColor;
				colorWater += clamp(specular,0, 1);
				if(material.y > 0){
					if(depthWater < depthTerrain){
						//In front of something

						float k = (depthTerrain - depthWater)*0.1;
						k = 1-k;
						k = exp(-5*k*k);
						// k = 1-k;
						outColor = vec4(k*colorWater + (1-k)*terrainColor, 1.0) ;
						// outColor = vec4(colorWater, 1.0);

					} else{
						//Behind
						discard;
					}
				} else{
					//No object
					outColor = vec4(colorWater, 1.0);
				}
				// outColor = outColor + 0.2*vec4(10.0 / 255.0, 40.0 / 255.0, 120.0 / 255.0, 0.1);
			} else{
				//Sky
				if(material.y > 0){
					discard;
				} else{
					vec3 specular = vec3(0.0);
					float dotSpec = clamp(dot(eyeVector, lightDirection), 0, 1);
					specular = (lightDirection.y) * ((pow(dotSpec, 512.0f)) * (shininess * 1.8f + 0.2f))* sunColor;
					specular += specular * 25 * (shininess - 0.05f) * sunColor;
					outColor = texture(skyTexture, directionToCoordinate(eyeVector))+clamp(vec4(specular, 1.0), 0, 1);
				}
			}
		}
	}

#endif
