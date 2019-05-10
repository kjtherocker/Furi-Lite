
uniform sampler2D u_Texture;
uniform float u_HealthPercent;

varying vec2 v_UV;
varying vec2 v_PosPercent;

void main()
{ 
  vec4 u_EmptyHealthBarColor = vec4(0.0f,0.0f,1.0f,1.0f);
    if(v_PosPercent.x > u_HealthPercent)
		{
		gl_FragColor =  vec4(0.0f,0.0f,0.0f,1.0f);
		}
		else
		{
		
			gl_FragColor = vec4(1.0f,1.0,1.0f,1.0f);
		}
}