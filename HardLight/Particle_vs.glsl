// vertex shader
// Written by: Sean Brown
#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;
uniform float coefficient;
uniform float percentFactor;

void main() {
	
	vec4 position4 = MVP * vec4(vertexPosition_modelspace, 1);
	
	float distance = length(-position4)/percentFactor;
	
	float pointSize = sqrt(1/(coefficient*distance*distance));
	gl_PointSize = pointSize;

	gl_Position = position4;

}
