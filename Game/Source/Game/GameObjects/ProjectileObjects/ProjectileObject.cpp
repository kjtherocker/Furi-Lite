#include "GamePCH.h"

ProjectileObject::ProjectileObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
    m_ProjectileLifetme = PROJECTILELIFETIME;
    m_Speed = PROJECTILESPEED;
    m_Playerpos = vec3(0, 0, 0);;
    m_IsShot = false;
    m_pScene->GetGame()->GetResourceManager()->GetSoundObj("MagicCircleSound");
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;
	m_HasPhysics = true;
    m_pPlayerObject = 0;
    m_ProjectileType = NullTypes;
	m_Phase = 0;
	m_TextureTimer = 0.5;
}

ProjectileObject::ProjectileObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
    m_ProjectileLifetme = PROJECTILELIFETIME;
    m_Speed = PROJECTILESPEED;
    m_Playerpos = vec3(0, 0, 0);
    m_IsShot = false;
    m_pScene->GetResourceManager()->GetSoundObj("MagicCircleSound");
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;
	m_HasPhysics = true;
    m_pPlayerObject = 0;
    m_ProjectileType = NullTypes;
	m_Phase = 0;
	m_TextureTimer = 0.5;
}

ProjectileObject::~ProjectileObject()
{
}

void ProjectileObject::Update(float deltatime)
{   
    m_ProjectileLifetme -= deltatime;

	if (m_Position.z > 0 || m_Position.z < 0)
	{
		m_Position.z = 0;
	}

    if (m_ProjectileLifetme <= 0)
    {
		if (m_pPool)
		{
			Destroy();
		}       
    }
	// Shoots in astraight line
	if (m_ProjectileType == Line)
	{
		if (m_IsShot == false)
		{
			
            SetMaterial(m_pMaterial);
			float m_Speed = PROJECTILESPEED;
	        m_Playerpos = m_pPlayerObject->GetPosition();
			m_DirectionVector = b2Vec2(m_Playerpos.x - m_Position.x, m_Playerpos.y - m_Position.y);
			m_DirectionVector.Normalize();
			m_IsShot = true;
		}
		m_Position += (vec3(m_DirectionVector.x, m_DirectionVector.y, m_Position.z) * m_Speed * deltatime);
		this->GetPhysicsBody()->ApplyLinearImpulseToCenter(b2Vec2(m_DirectionVector.x * m_Speed * deltatime, m_DirectionVector.y * m_Speed * deltatime), true);
		m_Position.x = this->GetPhysicsBody()->GetPosition().x;
		m_Position.y = this->GetPhysicsBody()->GetPosition().y;
	}
	// Moves slightly towards the player
	if (m_ProjectileType == Homing)
	{		
		m_TextureTimer -= deltatime;

		if (m_IsShot == false)
		{
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureHomingProjectile1"));
			float m_Speed = HOMINGPROJECTILESPEED;
			m_IsShot = true;
		}

		if (m_TextureTimer < 0.4f && m_Phase == 0)
		{
			m_Phase++;
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureHomingProjectile2"));
		}
		if (m_TextureTimer < 0.3f && m_Phase == 1)
		{
			m_Phase++;
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureHomingProjectile3"));
		}
		if (m_TextureTimer < 0.2f && m_Phase == 2)
		{
			m_Phase++;
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureHomingProjectile4"));
		}
		if (m_TextureTimer < 0.1f && m_Phase == 3)
		{
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureHomingProjectile5"));
		}
		if (m_TextureTimer < 0)
		{
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureHomingProjectile1"));
			m_TextureTimer = 0.5;
			m_Phase = 0;
		}

			m_Playerpos = m_pPlayerObject->GetPosition();
			m_DirectionVector = b2Vec2(m_Playerpos.x - m_Position.x, m_Playerpos.y - m_Position.y);
			m_DirectionVector.Normalize();

			m_Position += (vec3(m_DirectionVector.x, m_DirectionVector.y, m_Position.z) * m_Speed * deltatime);
			this->GetPhysicsBody()->ApplyLinearImpulseToCenter(b2Vec2(m_DirectionVector.x * m_Speed * deltatime, m_DirectionVector.y * m_Speed * deltatime), true);
			m_Position.x = this->GetPhysicsBody()->GetPosition().x;
			m_Position.y = this->GetPhysicsBody()->GetPosition().y;		
	}

}

void ProjectileObject::Reset()
{
    Destroy();
}


void ProjectileObject::Destroy()
{
    RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent(this);
    m_pScene->GetGame()->m_EventQueue.push(pEvent);
}

void ProjectileObject::RemoveFromScene()
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

void ProjectileObject::ResetTimers()
{
    m_IsShot = false;
    m_ProjectileLifetme = PROJECTILELIFETIME;
    m_Speed = PROJECTILESPEED;
}

void ProjectileObject::SetPlayer(PlayerObject * a_Playerobj)
{
    m_pPlayerObject = a_Playerobj;
}

void  ProjectileObject::SetPlayerPosition(vec3 pos)
{
    m_Playerpos = pos;
}

void ProjectileObject::FacePlayer()
{


}
