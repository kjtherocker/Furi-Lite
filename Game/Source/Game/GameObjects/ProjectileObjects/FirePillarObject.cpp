#include "GamePCH.h"

FirePillarObject::FirePillarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
    

    m_pScene->GetResourceManager()->GetSoundObj("MagicCircleSound");
}

FirePillarObject::FirePillarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
   


    m_pScene->GetResourceManager()->GetSoundObj("MagicCircleSound");
}

FirePillarObject::~FirePillarObject()
{
}

void FirePillarObject::Update(float deltatime)
{   
 
}

void FirePillarObject::Reset()
{
}






