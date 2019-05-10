uniform samplerCube u_TextureCube;

varying vec2 v_UV;
varying vec3 v_Cubeuv;

void main()
{
	vec3 ColorCube = textureCube( u_TextureCube, v_Cubeuv );

	gl_FragColor = vec4(ColorCube, 1);
}
