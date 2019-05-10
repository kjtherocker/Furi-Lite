
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

varying vec2 v_UV;
varying vec2 v_PosPercent;

void main()
{
    vec4 objectpos = a_Position;
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;

	v_PosPercent = (a_Position/2+abs(a_Position/2))/abs(a_Position);
    
	vec4 clippos = u_ProjMatrix * viewpos;

	

	// Store final position in gl_Position
    gl_Position = clippos;

	v_UV = a_UV;
}
