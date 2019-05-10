#include "GamePCH.h"
#include "ctime"

FBOmenu::FBOmenu(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{    
    m_LifeTime = 0;



}

FBOmenu::FBOmenu(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{  
    m_LifeTime = 0;


}

FBOmenu::~FBOmenu()
{
}

void FBOmenu::Update(float deltatime)
{   
    m_LifeTime -= deltatime;
    m_LifeTime *= 0.989f;

    if (m_LifeTime <= -0.5f)
    {
        SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible")); 
    }
    
}

void FBOmenu::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
	if (m_pMesh == 0)
		return;

	ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

	mat4 world;
	world.CreateSRT(m_Scale, m_Rotation, m_Position);

	m_pMesh->SetupAttributes(pShaderProgram);
	m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos, m_LifeTime);
	m_pMesh->Draw(pShaderProgram);
}

void FBOmenu::Destroy()
{

}

void FBOmenu::RemoveFromScene()
{

}

void FBOmenu::Reset()
{
    m_LifeTime = 0;
}






