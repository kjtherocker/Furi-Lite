
uniform sampler2D u_Texture;
uniform float u_LifeTime;

varying vec2 v_UV;
varying vec4 V_Color;

void main()
{

if(texture2D( u_Texture, v_UV ).w == 0)
	{
		discard;
	}
		vec4 color = texture2D( u_Texture, v_UV );



	V_Color += color;

	vec4 test = vec4(-u_LifeTime,-u_LifeTime,-u_LifeTime,-u_LifeTime);

    gl_FragColor  = vec4(V_Color.x - test.x,V_Color.y - test.y,V_Color.z -test.z,1) ;
}
