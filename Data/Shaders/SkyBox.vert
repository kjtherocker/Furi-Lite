
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

varying vec2 v_UV;
varying vec3 v_Cubeuv;

void main()
{
    vec4 objectpos = a_Position;

	//objectpos.z += 0.5;
	v_Cubeuv = objectpos.xyz;
	

    vec4 viewpos = u_ViewMatrix * vec4(objectpos.xyz,0);
    vec4 clippos = u_ProjMatrix * vec4(viewpos.xyz,1);


    gl_Position = clippos ;

    v_UV = a_UV;
}

