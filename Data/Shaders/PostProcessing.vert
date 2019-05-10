
attribute vec4 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;
uniform vec3 u_CameraPosition;

uniform vec3 u_RipplePos;
uniform float u_RippleDistance;

uniform float u_Time;

varying vec2 v_UV;
varying vec4 V_Color;

void main()


{
    vec4 objectpos = a_Position;

		float Amplitude = 0.4f;

	float wave = 6;
	float DistanceToPoint = length((objectpos.xyz + vec3(-3,1,-8)) / 25 );
	
	Amplitude -= DistanceToPoint;
	if(Amplitude <= 0.0f)
	{
		Amplitude = 0.0f;
	}

	objectpos.y += Amplitude * sin(-3.14 * DistanceToPoint * wave + u_Time);

    vec4 worldpos = u_WorldMatrix * objectpos;
    vec4 viewpos = u_ViewMatrix * worldpos;
    vec4 clippos = u_ProjMatrix * viewpos;

    gl_Position = clippos;

    v_UV = a_UV;

	
	V_Color = vec4(-objectpos.y,-objectpos.y, -objectpos.y,1);
}
