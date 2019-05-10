#ifndef __Mesh_H__
#define __Mesh_H__

class Mesh
{
protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

	int m_NumberOfLights;
	vec3 m_LightPos[5];
	vec3 m_LightColor[5];

    GLenum m_PrimitiveType;

public:
    Mesh();
    virtual ~Mesh();

    virtual void Init(VertexFormat* verts, int numverts, unsigned int* indices, int numindices, GLenum usage);
    virtual void Init(const void* verts, int numverts, int vertexbytesize, GLenum usage);

    virtual void SetupAttributes(ShaderProgram* pShaderProgram);
    virtual void SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos);
	virtual void SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, float particlepercentage);
	virtual void SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, float Health, float maxHealth);
	virtual void SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, int digit);
    virtual void SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, vec3 pos);
    virtual void Draw(ShaderProgram* pShaderProgram);

	void SetLightInfo(int numoflights, vec3 lightpos[], vec3 lightcolor[]);

    // The following functions are defined in MeshShapes.cpp
    static Mesh* CreateBox(vec2 size, bool flipx);
    static Mesh* CreateCircle(vec3 size);
    static Mesh * CreateCube(vec3 size);
    static Mesh * CreateInverseCube(vec3 size);
	static Mesh* CreatePlane(vec2 Origin, ivec2 NumVertices, vec2 Worldsize, vec2 uv);
    static Mesh* CreateFromObj(const char* objfilename);
};

class OurDebugDraw : public b2Draw
{
    Material* m_pMaterial;
    mat4* m_pViewMat;
    mat4* m_pProjMat;
    vec3 m_CamPos;

    virtual void DrawStuff(int mode, const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
};

#endif //__Game_H__
