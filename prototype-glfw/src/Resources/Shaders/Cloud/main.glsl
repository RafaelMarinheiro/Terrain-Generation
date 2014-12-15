
#ifdef _VERTEX_
	in vec2 position;
	out vec2 texCoord;

	void main(){
		gl_Position = vec4(position, 0.0, 1.0);
		texCoord = position;
	}
#endif


#ifdef _FRAGMENT_

uniform float time;

in vec2 texCoord;
out vec4 outColor;

uniform sampler2D cloudTexture;

uniform mat4 inverseMVP;

void main() {
    
    // vec3 u = 0.5*texCoord;
    vec2 u = (texCoord*0.5 + 0.5);
    vec3 uu = normalize(vec3(u.x, 1000, u.y));
    vec3 sky = texture(skyTexture, u).xyz;

    float color = texture(cloudTexture, texCoord + vec2(0, time*0.005)).x;

    outColor = vec4(sky*(1 + color), 1.0) ;
    // outColor = vec4(vec3(1.0)*color*0.6, 1.0);
}

#endif
