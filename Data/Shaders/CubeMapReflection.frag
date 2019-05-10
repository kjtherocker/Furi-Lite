
//uniform sampler2D u_Texture;
uniform samplerCube u_TextureCube;

uniform vec3 u_CameraPosition;

varying vec3 v_SurfaceToWorldPosition;
varying vec3 v_Normal;
varying vec2 v_UV;
varying vec3 v_Cubeuv;

void main()
{

	vec3 NormalizedNormal = normalize(v_Normal);
	//vec3 Result = Reflection * SurfaceColor;
	//vec4 color = vec4(Result, 1);

	vec3 CubeColor = textureCube( u_TextureCube, v_Cubeuv );
	//vec3 SurfaceColor = texture2D( u_Texture, v_UV ); 

	vec3 Surfacepos = v_SurfaceToWorldPosition; 

	vec3 Direction2Camera = Surfacepos - u_CameraPosition;

	vec3 NormalizedDirection2Camera = normalize(Direction2Camera);

	vec3 Reflection = reflect(NormalizedDirection2Camera, NormalizedNormal);

	vec4 ReflectedColor = texture(u_TextureCube, Reflection);

	//vec3 Reflection = reflect(-OppDirection2Camera, NormalizedNormal);

	//vec3 Result = texture(u_TextureCube, Reflection);

	//gl_FragColor = textureCube( u_TextureCube, v_Cubeuv );
    //gl_FragColor = texture2D( u_Texture, v_UV );

	 gl_FragColor = ReflectedColor;
	
}
