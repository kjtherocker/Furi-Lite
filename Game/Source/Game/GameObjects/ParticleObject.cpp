#include "GamePCH.h"
#include "ctime"

ParticleObject::ParticleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{    
	m_Lifetime = PARTICLELIFETIME;
	m_Speed = PARTICLESPEED;
    m_Created = false;
    m_pScene->GetResourceManager()->GetSoundObj("MagicCircleSound");
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;
	m_Phase = 0;
	m_pResource = 0;
    m_ParticleType = NullType;
}

ParticleObject::ParticleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{  
	m_Lifetime = PARTICLELIFETIME;
	m_Speed = PARTICLESPEED;
    m_Created = false;
    m_pScene->GetResourceManager()->GetSoundObj("MagicCircleSound");
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;
	m_Phase = 0;
	m_pResource = 0;
    m_ParticleType = NullType;
}

ParticleObject::~ParticleObject()
{
}

void ParticleObject::Update(float deltatime)
{   
	m_Lifetime -= deltatime;

    if (m_Lifetime <= 0)
    {
        if (m_pPool)
        {
            Destroy();
        }
    }

    if (m_ParticleType == NullType)
    {

    }
    else if (m_ParticleType == AnimatedParticle)
    {	// Changes its texture overtime to give it a nice effect
		if (m_Created == false)
		{
			this->SetScale(1.0f);
			m_Created = true;
		}

        if (m_Lifetime < 0.4f && m_Phase == 0)
        {
            m_Phase++;
            SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureRedParticle2"));
        }
        if (m_Lifetime < 0.3f && m_Phase == 1)
        {
            m_Phase++;
            SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureRedParticle3"));
        }
        if (m_Lifetime < 0.2f && m_Phase == 2)
        {
			m_Phase++;
            SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureRedParticle4"));
        }
		if (m_Lifetime < 0.1f && m_Phase == 3)
		{
			SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureRedParticle5"));
		}
    }
    else if (m_ParticleType == ExplosiveParticle)
    {	// Goes in a random direction. Spawned multiple at a time to give it a good effect
        if (m_Created == false)
        {
			this->SetScale(0.4f);

            float RandPosX = float((rand() % 10 + 1) - 5);
            float RandPosY = float((rand() % 10 + 1) - 5);
			m_Speed = float((rand() % 2 + 1) - 1);

            RandPosX = m_Position.x - RandPosX;
            RandPosY = m_Position.y - RandPosY;

            m_DirectionVector = b2Vec2(RandPosX - m_Position.x, RandPosY - m_Position.y);
            m_DirectionVector.Normalize();
            m_Created = true;
        }

        m_Position += (vec3(m_DirectionVector.x, m_DirectionVector.y, m_Position.z) * m_Speed * deltatime);
    }

}

void ParticleObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
	if (m_pMesh == 0)
		return;

	ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

	mat4 world;
	world.CreateSRT(m_Scale, m_Rotation, m_Position);

	m_pMesh->SetupAttributes(pShaderProgram);
	m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos, m_Lifetime);
	m_pMesh->Draw(pShaderProgram);
}

void ParticleObject::Destroy()
{
	if (m_pPool)
	{		
		RemoveFromSceneEvent* pEvent = new RemoveFromSceneEvent(this);
		m_pScene->GetGame()->m_EventQueue.push(pEvent);
	}
}

void ParticleObject::RemoveFromScene()
{
	GameObject::RemoveFromScene();

    SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureRedParticle1"));
    m_Phase = 0;
	m_Created = false;
	m_Lifetime = PARTICLELIFETIME;
	if (m_pPool)
	{
		m_pPool->ReturnObject(this);
	}
}






