
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

varying vec3 v_SurfaceToWorldPosition;
varying vec3 v_Normal;
varying vec2 v_UV;
varying vec3 v_Cubeuv;

void main()
{
   vec4 objectpos = a_Position;
    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    //vec4 viewpos = u_ViewMatrix * vec4(objectpos.xyz,0);
   // vec4 clippos = u_ProjMatrix * vec4(viewpos.xyz,1);


	//v_Normal = mat3(transpose(inverse(u_WorldMatrix))) * a_Normal;
	//v_SurfaceToWorldPosition = vec3(u_WorldMatrix * vec4(a_Position, 1));

	//gl_Position = u_WorldMatrix * vec4(a_Position, 1);

	 v_UV = a_UV;
	 //v_Cubeuv = a_UV;
	v_Cubeuv = objectpos.xyz;
	v_Normal = a_Normal;
	v_SurfaceToWorldPosition = worldpos.xyz;



    gl_Position = clippos;

}

