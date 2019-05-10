
uniform sampler2D u_Texture;
uniform float u_LifeTime;
varying vec2 v_UV;
varying vec4 v_Color;

void main()
{
	vec4 Texture = texture2D( u_Texture, v_UV );
	gl_FragColor = Texture;
}
