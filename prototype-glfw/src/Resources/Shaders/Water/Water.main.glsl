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
		vec3 n = vec3(-dx, -dy, 1.0);
		return normalize(n);
	}

	void main(){
		vec3 position = texture(gPositionMap, texCoord).xyz;
		vec3 material = texture(gMaterialMap, texCoord).xyz;
		float depthTerrain = length(eyePosition - position);

		vec4 pixelVector = inverseMVP*(vec4(texCoord.x, texCoord.y, 1.0, 1.0)); 
		vec3 eyeVector = (pixelVector.xyz/pixelVector.w) - eyePosition;
		eyeVector = normalize(eyeVector);

		// outColor = (vec4(normalize(position-eyePosition), 1.0));
		// outColor = vec4(eyeVector, 1.0);
		if(eyeVector.y == 0){
			discard;
		} else{
			// outColor = vec4(0.19, 0.27, 0.41, 1.0);
			float depthWater = -(eyePosition.y - waterHeight)/eyeVector.y;

			if(depthWater > 0){
				vec3 waterPosition = eyePosition + depthWater*eyeVector;
				vec3 waterNormal = waveNormal(waterPosition.x, waterPosition.z);
				if(material.y > 0){
					if(depthWater < depthTerrain){
						// outColor = vec4(0.19, 0.27, 0.41, 1.0);
						outColor = vec4(waterNormal, 1.0);
						} else{
							discard;
						}
					// outColor = vec4(0.19, 0.27, 0.41, 1.0);
				} else{
					// outColor = vec4(0.19, 0.27, 0.41, 1.0);
					outColor = vec4(waterNormal, 1.0);
				}
				// waterNormal = waterNormal.xzy;
				// // outColor = vec4(waterPosition, 1.0);
				// outColor = vec4(0.19, 0.27, 0.41, 1.0);
				// outColor = vec4(waterNormal, 1.0);
			} else{
				discard;
			}
		}
	}

#endif