// fragment shader
// Written by: Sean Brown
#version 330

out vec4 color;

uniform float radii;
uniform sampler2D sampler;

void main() {

	vec2 p = gl_PointCoord * 2.0 - vec2(1.0);
	if(dot(p, p) > radii)
		discard;
		

	color = texture2D(sampler, gl_PointCoord);

}
