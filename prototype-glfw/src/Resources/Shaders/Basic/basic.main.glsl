#ifdef _VERTEX_

	in vec2 position;

	void main() {
		gl_Position = vec4(position.x, position.y, 0.0, 1.0);
	}

#endif

#ifdef _FRAGMENT_

	out vec4 outColor;

	void main() {
		outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

#endif