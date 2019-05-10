
uniform sampler2D u_Texture;
uniform vec3 u_CameraPosition;

varying vec2 v_UV;

varying vec3 v_SurfaceToWorldPosition;

void main()
{
	vec3 LightPos = vec3(0,3,-1); 

	vec3 Surfacepos = v_SurfaceToWorldPosition; 

	vec3 Direction2Light =  LightPos - Surfacepos;

	vec3 Direction2Camera =  u_CameraPosition - Surfacepos;

	// Diffuse Percentage
	vec3 NormalizedDirection2Light = normalize(Direction2Light); 

	vec3 normal = vec3(0,1,0); 

	vec3 DiffusePercentage = dot(NormalizedDirection2Light, normal); 
	
	// Specular Percentage
	vec3 DirectionToCamera = normalize(u_CameraPosition - Surfacepos);

	vec3 SpecularLightVector = normalize(Direction2Light + Direction2Camera);

	vec3 SpecularPercentage = max(dot(SpecularLightVector, normal),0);

	// Distance
	float Distance = length(LightPos - Surfacepos);

	float FallOff = 1.0f;
	//(Will be a const)

	float DistancePercentage = 1.0f / (FallOff + (0.1f * Distance) + (0.01f * pow(Distance, 2)));

	 DiffusePercentage /= DistancePercentage;

	 SpecularPercentage /= DistancePercentage;


	vec3 LightColor = vec3(1,1,1); 

	vec3 SurfaceColor = vec3(0,0,1); 

	// Putting it all together
	//vec3 Result = AmbientPercentage * LightColor * SurfaceColor;

	//vec3 Result = DiffusePercentage * LightColor * SurfaceColor;

	//Result = Result * SpecularPercentage * LightColor * SurfaceColor;

	vec3 Result = (DiffusePercentage, + SpecularPercentage) * SurfaceColor;
	
	vec4 color = vec4(Result,1);
    gl_FragColor = color;
}