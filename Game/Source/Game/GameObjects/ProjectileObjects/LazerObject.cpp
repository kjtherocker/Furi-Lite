#include "GamePCH.h"

LazerObject::LazerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
    m_LazerLifetme = LAZERLIFETIME;
    m_IsShot = false;
    m_pScene->GetGame()->GetResourceManager()->GetSoundObj("MagicCircleSound");
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;
	m_HasPhysics = true;
}

LazerObject::LazerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
    m_LazerLifetme = LAZERLIFETIME;
    m_IsShot = false;
    m_pScene->GetGame()->GetResourceManager()->GetSoundObj("MagicCircleSound");
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;
    m_HasPhysics = true;
}

LazerObject::~LazerObject()
{
}

void LazerObject::Update(float deltatime)
{   
    m_LazerLifetme -= deltatime;

    if (m_LazerLifetme < 0)
    {
        if (m_pPool)
        {
            Destroy();
        }
    }
}

void LazerObject::Reset()
{
    Destroy();
}


void LazerObject::Destroy()
{
    RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent(this);
    m_pScene->GetGame()->m_EventQueue.push(pEvent);
}

void LazerObject::RemoveFromScene()
{
    GameObject::RemoveFromScene();

    ResetTimers();
    this->GetPhysicsBody()->SetActive(false);
    this->GetPhysicsBody()->SetAwake(false);


    if (m_pPool)
    {
        m_pPool->ReturnObject(this);
    }
}

void LazerObject::ResetTimers()
{
    m_IsShot = false;
    m_LazerLifetme = LAZERLIFETIME;
}
