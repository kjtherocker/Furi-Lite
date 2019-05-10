
uniform sampler2D u_Texture;

varying vec2 v_UV;
varying vec4 V_Color;


void main()
{
	vec4 color = texture2D( u_Texture, v_UV );

	color.z += 1.0;

	gl_FragColor = V_Color;
}
