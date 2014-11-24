#ifdef _VERTEX_
	in vec2 position;

	void main(){
		vec4 worldspace = vec4(position.x, 0.3*10.0, position.y, 1.0);
		gl_Position = projectionMatrix * (viewMatrix * (modelMatrix * worldspace));
		// gl_Position = vec4(position, 0.0, 1.0);
	}
#endif

#ifdef _FRAGMENT_
	// in float height;
	out vec4 outColor;

	void main(){
		outColor = vec4(0.19, 0.27, 0.41, 1.0);
		// outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
#endif