#include "GamePCH.h"

Mesh::Mesh()
{
    m_VBO = 0;
    m_IBO = 0;
    m_PrimitiveType = GL_TRIANGLES;

	int m_NumberOfLights = 0;
	vec3 m_LightPos[4] = {};
	vec3 m_LightColor[4] = {};
}

Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
}

void Mesh::Init(VertexFormat* verts, int numverts, unsigned int* indices, int numindices, GLenum usage)
{
    m_NumVerts = numverts;
    m_NumIndices = numindices;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numverts, verts, usage );

    // Generate and fill buffer with our indices.
    if( m_IBO == 0 )
        glGenBuffers( 1, &m_IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numindices, indices, usage );

    CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numverts, int vertexbytesize, GLenum usage)
{
    m_NumVerts = numverts;
    m_NumIndices = 0;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, vertexbytesize, verts, usage );

    CheckForGLErrors();
}

void Mesh::SetupAttributes(ShaderProgram* pShaderProgram)
{
    assert( m_VBO != 0 );

    // Bind our vertex and index buffers.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    if( m_IBO != 0 )
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLuint programhandle = pShaderProgram->GetProgram();

    // Get the attribute locations.
    GLint aPos = glGetAttribLocation( programhandle, "a_Position" );
    GLint aColor = glGetAttribLocation( programhandle, "a_Color" );
    GLint aUV = glGetAttribLocation( programhandle, "a_UV" );
    GLint aNormal = glGetAttribLocation( programhandle, "a_Normal" );

    // Setup our vbo and attributes.
    {
        // Setup the position attribute.
        assert( aPos != -1 );
        glVertexAttribPointer( aPos, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, pos) );
        glEnableVertexAttribArray( aPos );

        // Setup the color attribute.
        if( aColor != -1 )
        {
            glVertexAttribPointer( aColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, color) );
            glEnableVertexAttribArray( aColor );
        }

        // Setup the uv attribute.
        if( aUV != -1 )
        {
            glVertexAttribPointer( aUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv) );
            glEnableVertexAttribArray( aUV );
        }
        // Setup the Normals
        if (aNormal != -1)
        {
            glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, normal));
            glEnableVertexAttribArray(aNormal);
        }
    }
}

void Mesh::SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
	ShaderProgram* pShaderProgram = pMaterial->GetShader();
    GLuint programhandle = pShaderProgram->GetProgram();

    // Enable our shader program.
    glUseProgram( programhandle );

    // Get the uniform locations.
    GLint uWorldMatrix = glGetUniformLocation( programhandle, "u_WorldMatrix" );
	GLint uViewMatrix  = glGetUniformLocation( programhandle, "u_ViewMatrix" );
	GLint uProjMatrix  = glGetUniformLocation( programhandle, "u_ProjMatrix" );
	GLint uCameraPosition = glGetUniformLocation( programhandle, "u_CameraPosition" );
	GLint uTexture = glGetUniformLocation( programhandle, "u_Texture" );
    GLint uTexturecube = glGetUniformLocation(programhandle, "u_TextureCube");
    GLint uColor = glGetUniformLocation( programhandle, "u_Color" );
    GLint uTime = glGetUniformLocation( programhandle, "u_Time" );
    GLint uMoveLight = glGetUniformLocation(programhandle, "u_MoveLight");

    // Setup the texture.
	GLuint texturehandle = pMaterial->GetTexture();
    if( texturehandle != 0 && uTexture != -1 )
    {
        glActiveTexture( GL_TEXTURE0 + 0 );
        glBindTexture( GL_TEXTURE_2D, texturehandle );
        glUniform1i( uTexture, 0 );
    }
    if (texturehandle != 0 && uTexturecube != -1)
    {
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texturehandle);
        glUniform1i(uTexturecube, 1);
    }


	if( uWorldMatrix != -1 )
	{
		glUniformMatrix4fv( uWorldMatrix, 1, false, &pMatWorld->m11 );
	}
	
	if( uViewMatrix != -1 )
	{
		glUniformMatrix4fv( uViewMatrix, 1, false, &pMatView->m11 );
	}
	
	if( uProjMatrix != -1 )
    {
        glUniformMatrix4fv( uProjMatrix, 1, false, &pMatProj->m11 );
    }

    if( uCameraPosition != -1 )
    {
        glUniform3f( uCameraPosition, campos.x, campos.y, campos.z );
    }
	
	if( uColor != -1 )
    {
		MyColor color = pMaterial->GetColor();
        glUniform4f( uColor, color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f );
    }

    // Setup time.
    if( uTime != -1 )
    {
        glUniform1f( uTime, (float)GetSystemTimeSinceGameStart() );
    }

    if (uMoveLight != -1)
	{
		vec3 pos = 0;
        glUniform3f(uMoveLight, pos.x, pos.y, pos.z);
    }

    CheckForGLErrors();
}


void Mesh::SetupUniforms(Material * pMaterial, mat4 * pMatWorld, mat4 * pMatView, mat4 * pMatProj, vec3 campos, float particlepercentage)
{
	ShaderProgram* pShaderProgram = pMaterial->GetShader();
	GLuint programhandle = pShaderProgram->GetProgram();

	// Enable our shader program.
	glUseProgram(programhandle);

	// Get the uniform locations.
	GLint uWorldMatrix = glGetUniformLocation(programhandle, "u_WorldMatrix");
	GLint uViewMatrix = glGetUniformLocation(programhandle, "u_ViewMatrix");
	GLint uProjMatrix = glGetUniformLocation(programhandle, "u_ProjMatrix");
	GLint uCameraPosition = glGetUniformLocation(programhandle, "u_CameraPosition");
	GLint uTexture = glGetUniformLocation(programhandle, "u_Texture");
	GLint uColor = glGetUniformLocation(programhandle, "u_Color");
	GLint uTime = glGetUniformLocation(programhandle, "u_Time");
	GLint uLifeTime = glGetUniformLocation(programhandle, "u_LifeTime");

	// Setup the texture.
	GLuint texturehandle = pMaterial->GetTexture();
	if (texturehandle != 0 && uTexture != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texturehandle);
		glUniform1i(uTexture, 0);
	}

	if (uWorldMatrix != -1)
	{
		glUniformMatrix4fv(uWorldMatrix, 1, false, &pMatWorld->m11);
	}

	if (uViewMatrix != -1)
	{
		glUniformMatrix4fv(uViewMatrix, 1, false, &pMatView->m11);
	}

	if (uProjMatrix != -1)
	{
		glUniformMatrix4fv(uProjMatrix, 1, false, &pMatProj->m11);
	}

	if (uCameraPosition != -1)
	{
		glUniform3f(uCameraPosition, campos.x, campos.y, campos.z);
	}

	if (uColor != -1)
	{
		MyColor color = pMaterial->GetColor();
		glUniform4f(uColor, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	if (uLifeTime != -1)
	{

		glUniform1f(uLifeTime, particlepercentage);
	}

	// Setup time.
	if (uTime != -1)
	{
		glUniform1f(uTime, (float)GetSystemTimeSinceGameStart());
	}

	CheckForGLErrors();
}

void Mesh::SetupUniforms(Material * pMaterial, mat4 * pMatWorld, mat4 * pMatView, mat4 * pMatProj, vec3 campos, float Health, float maxHealth)
{
	ShaderProgram* pShaderProgram = pMaterial->GetShader();
	GLuint programhandle = pShaderProgram->GetProgram();

	// Enable our shader program.
	glUseProgram(programhandle);

	// Get the uniform locations.
	GLint uWorldMatrix = glGetUniformLocation(programhandle, "u_WorldMatrix");
	GLint uViewMatrix = glGetUniformLocation(programhandle, "u_ViewMatrix");
	GLint uProjMatrix = glGetUniformLocation(programhandle, "u_ProjMatrix");
	GLint uCameraPosition = glGetUniformLocation(programhandle, "u_CameraPosition");
	GLint uTexture = glGetUniformLocation(programhandle, "u_Texture");
	GLint uColor = glGetUniformLocation(programhandle, "u_Color");
	GLint uTime = glGetUniformLocation(programhandle, "u_Time");
	GLint uHealthPercent = glGetUniformLocation(programhandle, "u_HealthPercent");


	// Setup the texture.
	GLuint texturehandle = pMaterial->GetTexture();
	if (texturehandle != 0 && uTexture != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texturehandle);
		glUniform1i(uTexture, 0);
	}

	if (uWorldMatrix != -1)
	{
		glUniformMatrix4fv(uWorldMatrix, 1, false, &pMatWorld->m11);
	}

	if (uViewMatrix != -1)
	{
		glUniformMatrix4fv(uViewMatrix, 1, false, &pMatView->m11);
	}

	if (uProjMatrix != -1)
	{
		glUniformMatrix4fv(uProjMatrix, 1, false, &pMatProj->m11);
	}

	if (uCameraPosition != -1)
	{
		glUniform3f(uCameraPosition, campos.x, campos.y, campos.z);
	}

	if (uColor != -1)
	{
		MyColor color = pMaterial->GetColor();
		glUniform4f(uColor, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	if (uHealthPercent != -1)
	{

		glUniform1f(uHealthPercent, Health / maxHealth);
	}

	// Setup time.
	if (uTime != -1)
	{
		glUniform1f(uTime, (float)GetSystemTimeSinceGameStart());
	}

	CheckForGLErrors();
}

void Mesh::SetupUniforms(Material * pMaterial, mat4 * pMatWorld, mat4 * pMatView, mat4 * pMatProj, vec3 campos, int digit)
{
	ShaderProgram* pShaderProgram = pMaterial->GetShader();
	GLuint programhandle = pShaderProgram->GetProgram();

	// Enable our shader program.
	glUseProgram(programhandle);

	// Get the uniform locations.
	GLint uWorldMatrix = glGetUniformLocation(programhandle, "u_WorldMatrix");
	GLint uViewMatrix = glGetUniformLocation(programhandle, "u_ViewMatrix");
	GLint uProjMatrix = glGetUniformLocation(programhandle, "u_ProjMatrix");
	GLint uCameraPosition = glGetUniformLocation(programhandle, "u_CameraPosition");
	GLint uTexture = glGetUniformLocation(programhandle, "u_Texture");
	GLint uTexturecube = glGetUniformLocation(programhandle, "u_TextureCube");
	GLint uScoreDigitValue = glGetUniformLocation(programhandle, "u_ScoreDigitValue");
	GLint uColor = glGetUniformLocation(programhandle, "u_Color");
	GLint uTime = glGetUniformLocation(programhandle, "u_Time");

	// Setup the texture.
	GLuint texturehandle = pMaterial->GetTexture();
	if (texturehandle != 0 && uTexture != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texturehandle);
		glUniform1i(uTexture, 0);
	}
	if (texturehandle != 0 && uTexturecube != -1)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texturehandle);
		glUniform1i(uTexturecube, 1);
	}


	if (uWorldMatrix != -1)
	{
		glUniformMatrix4fv(uWorldMatrix, 1, false, &pMatWorld->m11);
	}

	if (uViewMatrix != -1)
	{
		glUniformMatrix4fv(uViewMatrix, 1, false, &pMatView->m11);
	}

	if (uProjMatrix != -1)
	{
		glUniformMatrix4fv(uProjMatrix, 1, false, &pMatProj->m11);
	}

	if (uCameraPosition != -1)
	{
		glUniform3f(uCameraPosition, campos.x, campos.y, campos.z);
	}

	if (uColor != -1)
	{
		MyColor color = pMaterial->GetColor();
		glUniform4f(uColor, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	if (uScoreDigitValue != -1)
	{
		glUniform1i(uScoreDigitValue, digit);
	}

	// Setup time.
	if (uTime != -1)
	{
		glUniform1f(uTime, (float)GetSystemTimeSinceGameStart());
	}

	CheckForGLErrors();
}

void Mesh::SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, vec3 pos)
{
    ShaderProgram* pShaderProgram = pMaterial->GetShader();
    GLuint programhandle = pShaderProgram->GetProgram();

    // Enable our shader program.
    glUseProgram(programhandle);

    // Get the uniform locations.
    GLint uWorldMatrix = glGetUniformLocation(programhandle, "u_WorldMatrix");
    GLint uViewMatrix = glGetUniformLocation(programhandle, "u_ViewMatrix");
    GLint uProjMatrix = glGetUniformLocation(programhandle, "u_ProjMatrix");
    GLint uCameraPosition = glGetUniformLocation(programhandle, "u_CameraPosition");
    GLint uTexture = glGetUniformLocation(programhandle, "u_Texture");
    GLint uTexturecube = glGetUniformLocation(programhandle, "u_TextureCube");
    GLint uBossPos = glGetUniformLocation(programhandle, "u_BossPos");
    GLint uColor = glGetUniformLocation(programhandle, "u_Color");
    GLint uTime = glGetUniformLocation(programhandle, "u_Time");

    // Setup the texture.
    GLuint texturehandle = pMaterial->GetTexture();
    if (texturehandle != 0 && uTexture != -1)
    {
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, texturehandle);
        glUniform1i(uTexture, 0);
    }
    if (texturehandle != 0 && uTexturecube != -1)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texturehandle);
        glUniform1i(uTexturecube, 1);
    }


    if (uWorldMatrix != -1)
    {
        glUniformMatrix4fv(uWorldMatrix, 1, false, &pMatWorld->m11);
    }

    if (uViewMatrix != -1)
    {
        glUniformMatrix4fv(uViewMatrix, 1, false, &pMatView->m11);
    }

    if (uProjMatrix != -1)
    {
        glUniformMatrix4fv(uProjMatrix, 1, false, &pMatProj->m11);
    }

    if (uCameraPosition != -1)
    {
        glUniform3f(uCameraPosition, campos.x, campos.y, campos.z);
    }

	if (uBossPos != -1)
	{
		vec3 poss = pos;

		if (poss.x == 8)
		{
			bool holyfuck = true;
		}
		glUniform3f(uBossPos, pos.x, pos.y, pos.z);
	}

    if (uColor != -1)
    {
        MyColor color = pMaterial->GetColor();
        glUniform4f(uColor, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    }


    // Setup time.
    if (uTime != -1)
    {
        glUniform1f(uTime, (float)GetSystemTimeSinceGameStart());
    }

    CheckForGLErrors();
}

void Mesh::Draw(ShaderProgram* pShaderProgram)
{
    GLuint programhandle = pShaderProgram->GetProgram();

    // Draw the shape.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }

    GLint aPos = glGetAttribLocation( programhandle, "a_Position" );
    GLint aColor = glGetAttribLocation( programhandle, "a_Color" );
    GLint aUV = glGetAttribLocation( programhandle, "a_UV" );
    GLint aNormal = glGetAttribLocation( programhandle, "a_Normal" );

    // Disable the attribute arrays used
    glDisableVertexAttribArray( aPos );

    if( aColor != -1 )
        glDisableVertexAttribArray( aColor );

    if( aUV != -1 )
        glDisableVertexAttribArray( aUV );

    if( aNormal != -1 )
        glDisableVertexAttribArray( aNormal );

    CheckForGLErrors();
}

void OurDebugDraw::DrawStuff(int mode, const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    GLuint programhandle = m_pMaterial->GetShader()->GetProgram();

    GLint aPos = glGetAttribLocation(programhandle, "a_Position");

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, vertices);
    glEnableVertexAttribArray(aPos);

    //Mesh* m_pMesh;
    //m_pMesh->SetupUniforms(m_pMaterial, 0, m_pViewMat, m_pProjMat, m_CamPos);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glDrawArrays(mode, 0, vertexCount);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

}

void OurDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    DrawStuff(GL_TRIANGLES, vertices, vertexCount, color);
    b2Color Color = color;
    Color.a = 1.0f;
    DrawStuff(GL_LINES, vertices, vertexCount, Color);
}

void Mesh::SetLightInfo(int numoflights, vec3 lightpos[], vec3 lightcolor[])
{
	//m_NumberOfLights = numoflights;

 	vec3 m_LightPos[] = { lightpos[0],lightpos[1],lightpos[2],lightpos[3],lightpos[4] };
	vec3 m_LightColor[] = { lightcolor[0],lightcolor[1],lightcolor[2],lightcolor[3],lightcolor[4] };
}
