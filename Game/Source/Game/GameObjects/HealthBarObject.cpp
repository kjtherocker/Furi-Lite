#include "GamePCH.h"

HealthBarObject::HealthBarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
	: GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
	m_MaxHealth = 300;
	m_Health = 300;
}

HealthBarObject::HealthBarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{

    m_MaxHealth = 300;
    m_Health = 300;

}

HealthBarObject::~HealthBarObject()
{
}

void HealthBarObject::Update(float deltatime)
{

}

void HealthBarObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
    if (m_pMesh == 0)
        return;

    ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

    mat4 world;
    world.CreateSRT(m_Scale, m_Rotation, m_Position);

    m_pMesh->SetupAttributes(pShaderProgram);
    m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos,float( m_Health ),float(m_MaxHealth));
    m_pMesh->Draw(pShaderProgram);
}

void HealthBarObject::SetMaxHealth(int maxhealth)
{
    m_MaxHealth = maxhealth;
}

void HealthBarObject::SetHealth(int health)
{
    m_Health = health;
}

void HealthBarObject::DecreaseHealth(int health)
{
    m_Health -= health;

}
