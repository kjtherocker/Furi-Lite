#include "GamePCH.h"

SkyBoxObject::SkyBoxObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
	: GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
    m_HasPhysics = false;
}

SkyBoxObject::SkyBoxObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
    m_HasPhysics = false;
}

SkyBoxObject::~SkyBoxObject()
{
}

void SkyBoxObject::Update(float deltatime)
{
    m_Rotation += 5 * deltatime;
}

void SkyBoxObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
    if (m_pMesh == 0)
        return;

    ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

    mat4 world;
    world.CreateSRT(m_Scale, m_Rotation, m_Position);

    m_pMesh->SetupAttributes(pShaderProgram);
    m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos, vec3(0));
    m_pMesh->Draw(pShaderProgram);
}
