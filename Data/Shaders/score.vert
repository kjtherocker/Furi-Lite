
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;
uniform int u_ScoreDigitValue;
varying vec2 v_UV;

void main()
{
    vec4 objectpos = a_Position;
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;

	v_UV = a_UV;

	v_UV *= vec2(0.1f,1.0f);
	v_UV += vec2((0.1 * u_ScoreDigitValue), 1.0f);

}
