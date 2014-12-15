
#ifdef _VERTEX_
	in vec2 position;
	out vec2 texCoord;

	void main(){
		gl_Position = vec4(position, 0.0, 1.0);
		texCoord = position;
	}
#endif


#ifdef _FRAGMENT_

in vec2 texCoord;
out vec4 outColor;

uniform vec3 lightDirection;

void main() {
    vec2 u = texCoord;
    float l = dot(u, u);
    vec4 result = vec4(0.0);

    // if (l <= 1.0) {
        vec3 extinction;
        result.rgb = skyRadiance(earthPos, inverseStereographicProjection(u), lightDirection.xzy, extinction);
        result.rgb = hdr(result.rgb);
    // }

    outColor = result;
}

#endif
