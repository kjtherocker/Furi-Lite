
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;
uniform vec3 u_MoveLight;
uniform vec3 u_BossPos;

varying vec3 v_SurfaceToWorldPosition;
varying vec3 v_Normal;
varying vec3 v_MoveLight;
varying vec3 v_BossPos;
varying vec2 v_UV;

void main()
{
    vec4 objectpos = a_Position;
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;

    v_UV = a_UV;
	v_Normal = a_Normal;
	v_SurfaceToWorldPosition = worldpos.xyz;
	v_MoveLight = u_MoveLight;
	v_BossPos = u_BossPos;
}
