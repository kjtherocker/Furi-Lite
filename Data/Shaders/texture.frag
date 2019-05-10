
uniform sampler2D u_Texture;

varying vec2 v_UV;

void main()
{
if(texture2D( u_Texture, v_UV ).w == 0)
	{
		discard;
	}
    gl_FragColor = texture2D( u_Texture, v_UV );
}
