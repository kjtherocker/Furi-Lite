#include "GamePCH.h"

MagicCircleObject::MagicCircleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
	m_MagicCircleObjectLifetme = 0;
    m_AttackTimer = MAGICCIRCLEATTACKTIMER;
	m_pPool = 0;
    m_IsAttacking = false;
    m_PillarDeath = false;
    m_PilarRotation = 0.0f;
    m_pFirePillar = 0;
	m_HasPhysics = false;

    m_Mask = PhysicsCategory_Player;
    m_Category = PhysicsCategory_Default;

}

MagicCircleObject::MagicCircleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
    m_MagicCircleObjectLifetme = 0;
    m_AttackTimer = MAGICCIRCLEATTACKTIMER;
	m_pPool = 0;
    m_IsAttacking = false;
    m_PillarDeath = false;
    m_PilarRotation = 0.0f;
    m_pFirePillar = 0;
	m_HasPhysics = false;

    
    m_Mask = PhysicsCategory_Player;
    m_Category = PhysicsCategory_Default;


}

MagicCircleObject::~MagicCircleObject()
{
    if (m_pFirePillar != nullptr)
    {
        if (m_PillarDeath != true)
        {
            delete m_pFirePillar;
        }
    }
}

void MagicCircleObject::Update(float deltatime)
{
    float speed = MAGICCIRCLESPEED;
    float lifetime = MAGICCIRCLELIFETIME;  

    m_AttackTimer -= deltatime;

	m_MagicCircleObjectLifetme += speed * deltatime;

	m_Rotation.z += m_MagicCircleObjectLifetme * deltatime;

    std::string m_name;

	if (m_AttackTimer < 0)
	{

		if (m_IsAttacking == false)
		{
			if (m_pGame->GetIsSoundOn())
			{
				
				m_pGame->GetSoundPlayer()->PlaySound(m_pGame->GetSoundCue()->GetSound(SoundType_Projectile));
			}
			// Creates afire pillar that will damage the player
			m_pFirePillar = new FirePillarObject(m_pScene, "MagicPillar" + this->GetName(), vec3(m_Position.x, m_Position.y, m_Position.z -0.5f), vec3(0, 0, 0), vec3(5.5f, 5.5f, 3.5f), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("TextureFirePilar"),m_pGame);
			m_pFirePillar->SetRenderOrder(3);
            m_pFirePillar->SetScene(m_pScene);
            m_pFirePillar->AddPhysicsCircle(1.0f, true, true, 1, true);
            m_pFirePillar->GetPhysicsBody()->ApplyForce(b2Vec2(0, 0), b2Vec2(0.0f, 0.0f), true);
		}
		m_IsAttacking = true;
	}
  

    if (m_AttackTimer <-0.5f)
    {
        m_PillarDeath = true;
        Destroy();
    }

    if (m_IsAttacking)
    {      
        if (m_PillarDeath == false)
        {
            m_PilarRotation += 50.0f * deltatime;
            m_pFirePillar->SetRotation(vec3(0, 0, m_PilarRotation));
            if (m_PilarRotation > 359)
            {
                m_PilarRotation = 0;
            }
        }
    }
}

void MagicCircleObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
    if (m_pMesh == 0)
        return;

    ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

    mat4 world;
    world.CreateSRT(m_Scale, m_Rotation, m_Position);

    m_pMesh->SetupAttributes(pShaderProgram);
    m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos);
    m_pMesh->Draw(pShaderProgram);
    if (m_pFirePillar != nullptr)
    {
        if (m_PillarDeath != true)
        {
            m_pFirePillar->Draw(renderorder, pMatView, pMatProj, campos);
        }
    }
}

void MagicCircleObject::ResetTimers()
{
    m_AttackTimer = MAGICCIRCLEATTACKTIMER;
    m_MagicCircleObjectLifetme = 0;
    m_PilarRotation = 0;
    m_IsAttacking = false;
    m_PillarDeath = false;
}

void MagicCircleObject::Reset()
{
    m_PillarDeath = true;
    Destroy();
}

void MagicCircleObject::RemoveFromScene()
{
    GameObject::RemoveFromScene();

    ResetTimers();
    
    if (m_pPool)
    {
        m_pPool->ReturnObject(this);
    }
    
}

void MagicCircleObject::Destroy()
{     
		if (m_pFirePillar != nullptr)
		{
			delete m_pFirePillar;
            m_pFirePillar = 0;
		}

        RemoveFromSceneEvent* pEvent1 = new RemoveFromSceneEvent(this);
        m_pScene->GetGame()->m_EventQueue.push(pEvent1);
	
}
