
uniform sampler2D u_Texture;


uniform vec3 u_CameraPosition;

varying vec2 v_UV;
varying vec3 v_SurfaceToWorldPosition;
varying vec3 v_Normal;
varying vec3 v_MoveLight;
varying vec3 v_BossPos;



void main()
{
	float AmbientStrength = 0.3f;
	float SpecularStrength = 2.0f;
	vec3 LightColorArray[5] = {vec3(1, 1, 1),  vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1),  vec3(1, 5, 1) };
	vec3 fdgd = vec3(8, 8, 5);
	vec3 LightPosArray[5] = {vec3(8, 8, -2),  vec3(-8, -8, -2), vec3(-8, 8, -2), vec3(8, -8, -2), vec3(fdgd.x, fdgd.y,  fdgd.z) };
	vec3 Result = 0;
	//(Will be a const)
	float FallOff = 0.1f;
	vec3 SurfaceColor = texture2D( u_Texture, v_UV ); 

	for(int i = 0; i < 4; i++)
	{

	vec3 LightPos = LightPosArray[i]; 
	vec3 LightColor = LightColorArray[i]; 

	vec3 Surfacepos = v_SurfaceToWorldPosition; 

	vec3 NormalizedNormal = normalize(v_Normal);

	vec3 Direction2Light =  LightPos - Surfacepos;

	vec3 Direction2Camera =  u_CameraPosition - Surfacepos;

	// Diffuse Percentage
	vec3 NormalizedDirection2Light = normalize(Direction2Light);
	
	vec3 lightDir = normalize(LightPos - Surfacepos);
	
	float Diffuse = (max(dot(NormalizedNormal, lightDir), 0.0));

	vec3 DiffusePercentage = Diffuse *  LightColor;
	
	// Specular Percentage

	vec3 DirectionToCamera = normalize(u_CameraPosition - Surfacepos);

	vec3 ReflectDirection = reflect(-lightDir, NormalizedNormal);

	float SpecularPower = pow(max(dot(DirectionToCamera, ReflectDirection), 0.0), 2);

	vec3 SpecularPercentage = SpecularStrength * SpecularPower * LightColor;

	// Distance
	float Distance = length(LightPos - Surfacepos);

	float DistancePercentage = 1.0f / (FallOff + (0.1f * Distance) + (0.01f * pow(Distance, 2)));

	 //DiffusePercentage /= DistancePercentage;

	 //SpecularPercentage /= DistancePercentage;

	// Putting it all together

    vec3 Ambient = AmbientStrength * LightColor;

	//vec3 Result = DiffusePercentage * LightColor * SurfaceColor;

	//Result = Result * SpecularPercentage * LightColor * SurfaceColor;

	Result += (Ambient + DiffusePercentage + SpecularPercentage) * SurfaceColor;
	}
	//Result /= 5;

	vec4 color = vec4(Result,1);
    gl_FragColor = color;

	//gl_FragColor = texture2D( u_Texture, v_UV );

	//if(texture2D( u_Texture, v_UV ).w == 0)
	//{
		//discard;
	//}
}