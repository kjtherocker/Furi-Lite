#include "GamePCH.h"

RedBossObject::RedBossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : BossObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
    m_TestTimer = 3;
    m_MagicCircleTimer = MAGICCIRCLETIMER;
    m_ProjectileTimer = PROJECTILETIMER;
    m_AttackTimer = EASYATTACKTIMER;
    m_LazerTimer = LAZERATTACKTIMER;
    m_PlayerObject = 0;
    m_AttackDone = true;
    m_MagicCircleCreated = false;

    m_BossState = (BossState)&RedBossObject::Start;
    (this->*m_BossState)(0);

    AddProjectileToPool();
    AddMagicCircleToPool();
    AddParticleToPool();
    AddLazerToPool();

    m_TeleportNode1 = vec3(0, 0, 0);
    m_TeleportNode2 = vec3(-5, -5, 1);
    m_TeleportNode3 = vec3(5, 5, 0);
    m_TeleportNode4 = vec3(5, -5, -1);
    m_TeleportNode5 = vec3(-5, 5, 0);
    m_TeleportNode6 = vec3(3, 0, -1);
    m_TeleportNode7 = vec3(-4, 1, 2);
    m_TeleportNode8 = vec3(-1, 4, -2);
    m_TeleportNode9 = vec3(3, -2, 1);

    m_ProjectileFinish = 0;
    m_StateProjectileTimer = 1;
    m_pParticleType = NullType;
    m_ProjectileType = NullTypes;

    randomvalue = 0;

    m_pScene->m_pGameObjects["BossHealthbar"] = new HealthBarObject(m_pScene, "BossHealthbar", vec3(4, 7.0f, -1.1f), vec3(0, 0, 0), vec3(6, 1, 1), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("HealthMegaman"), m_pGame);

    m_pScene->m_pGameObjects["BossHealthbar"]->SetRenderOrder(2);
    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;

    m_Count = 0;
    m_LazerCount = 0;
    m_ProCount = 0;
    m_Health = 25;
    m_MaxHealth = 25;
    m_ParticlesToAdd = 0;

    //new
    m_Attack = 0;
    m_Movement = 0;
    m_Node = 0;
    m_TeleportTimer = 0;
    m_TeleRand = 0;
    m_Setup = false;
}

RedBossObject::RedBossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : BossObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
    m_TestTimer = 3.0f;
    m_MagicCircleTimer = MAGICCIRCLETIMER;
    m_ProjectileTimer = PROJECTILETIMER;
    m_AttackTimer = EASYATTACKTIMER;
    m_LazerTimer = LAZERATTACKTIMER;
    m_PlayerObject = 0;
    m_AttackDone = true;
    m_MagicCircleCreated = false;

    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;

    //Setting the statemachine to a method that does nothing
    m_BossState = &RedBossObject::Start;
    (this->*m_BossState)(0);

    AddProjectileToPool();
    AddMagicCircleToPool();
    AddParticleToPool();
    AddLazerToPool();

    m_TeleportNode1 = vec3(0, 0, 0);
    m_TeleportNode2 = vec3(-5, -5, 1);
    m_TeleportNode3 = vec3(5, 5, 0);
    m_TeleportNode4 = vec3(5, -5, -1);
    m_TeleportNode5 = vec3(-5, 5, 0);
    m_TeleportNode6 = vec3(3, 0, -1);
    m_TeleportNode7 = vec3(-4, 1, 2);
    m_TeleportNode8 = vec3(-1, 4, -2);
    m_TeleportNode9 = vec3(3, -2, 1);


    m_ProjectileFinish = 0;
    m_StateProjectileTimer = 1;
    m_pParticleType = NullType;
    m_ProjectileType = Homing;

    m_pScene->m_pGameObjects["BossHealthbar1"] = new HealthBarObject(m_pScene, "BossHealthbar1", vec3(4, 7.0f, -1.1f), vec3(0, 0, 0), vec3(6, 1, 1), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("HealthMegaman"), m_pGame);
    m_pScene->m_pGameObjects["BossHealthbar1"]->SetRenderOrder(2);

    randomvalue = 0;

    m_Count = 0;
    m_LazerCount = 0;
    m_ProCount = 0;
    m_Health = 25;
    m_MaxHealth = 25;
    m_ParticlesToAdd = 2;

    //new
    m_Attack = 0;
    m_Movement = 0;
    m_Node = 0;
    m_TeleportTimer = 0;
    m_TeleRand = 0;
    m_Setup = false;
}

RedBossObject::~RedBossObject()
{
}

void RedBossObject::Update(float deltatime)
{
    m_TestTimer -= deltatime;
    m_AttackTimer -= deltatime;
	
	if (m_pGame->GetUserInterface() == false)
	{
		m_pScene->m_pGameObjects["BossHealthbar1"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
	}
	else
	{
		m_pScene->m_pGameObjects["BossHealthbar1"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("HealthMegaman"));
	}

	this->GetPhysicsBody()->ApplyForce(b2Vec2(0, 0), b2Vec2(0.0f, 0.0f), true);

    //This updates every statemachine all at once
    (this->*m_BossState)(deltatime);

    //Randomize Which attack the boss will do
    if (m_AttackDone == true)
    {
        m_Attack = int((rand() % 4 + 1));
        m_Movement = int((rand() % 2 + 1));
        m_TeleRand = float((rand() % 10 - 5));
        m_Setup = false;
    }

    //Set Line or Homing Projectiles
    if (m_Attack == 1)
    {
        m_ProjectileType = Line;
    }
    if (m_Attack == 2)
    {
        m_ProjectileType = Homing;
    }

	// Sets up the debug mode and changes the attacks
    if (m_pGame->GetTestMode())
    {
        ImGui::Begin("BossWindow", 0, 0);

        if (ImGui::Button("MagicCircle Attack"))
        {
            m_Attack = 4;
            m_AttackTimer = 0;
            m_AttackDone = true;
        }

        if (ImGui::Button("Lazer Attack"))
        {
            m_Attack = 3;
            m_AttackTimer = 0;
            m_AttackDone = true;
            m_Movement = 3;
        }

        if (ImGui::Button("Homing Projectile Attack"))
        {
            m_Attack = 2;
            m_ProjectileType = Homing;
            m_AttackDone = true;
        }

        if (ImGui::Button("Line Projectile Attack"))
        {
            m_Attack = 1;
            m_ProjectileType = Line;
            m_AttackDone = true;
        }

        if (ImGui::Button("Teleport"))
        {
            m_Movement = 1;
            m_AttackDone = true;
        }

        if (ImGui::Button("Orbit"))
        {
            m_Movement = 2;
            m_AttackDone = true;
        }
        ImGui::End();
    }
	// Sets the attacks
    if (m_AttackDone == true)
    {
        if (m_Attack == 0)
        {
            m_BossState = &RedBossObject::Start;
        }
        if (m_Attack == 1)
        {
            m_BossState = &RedBossObject::ProjectileAttack;
        }
        if (m_Attack == 2)
        {
            m_BossState = &RedBossObject::ProjectileAttack;
        }
        if (m_Attack == 3)
        {
            m_Movement = 3;
            m_BossState = &RedBossObject::LazerAttack;
        }
        if (m_Attack == 4)
        {
            m_BossState = &RedBossObject::GroundAttack;
        }
        m_AttackDone = false;
    }

    if (m_Movement == 1)
    {
        //Orbiting Movement
        float angledist = 360.0f;
        float radians = (angledist) * (PI / 180.0f) + (float)GetSystemTime();
        float radius = 5.0f;

        vec3 pos = vec3(m_PlayerObject->GetPosition().x, m_PlayerObject->GetPosition().y + m_TeleRand, m_PlayerObject->GetPosition().z);

        this->SetPosition(pos + CalculateOffset(radians, radius));
    }
    if (m_Movement == 2)
    {
        // Teleport Arround
        if (m_TeleportTimer <= 0)
        {
			if (m_pGame->GetDiffculty() == false)
			{
				m_TeleportTimer = BOSSTELEPORTTIMER;
			} 
			else
			{
				m_TeleportTimer = BOSSTELEPORTTIMER + 1.0f;
			}
            m_Node = int((rand() % 9 + 1));
            SetTeleportPosition(m_Node);
        }
    }
    if (m_Movement == 3)
    {	// Lazer Movement
        if (m_Setup == false)
        {
            this->SetPosition(vec3(-6, 7, 0));
            m_Setup = true;
        }
        vec3 pos = vec3(this->GetPosition().x, this->GetPosition().y + (-1.0f * 5 *deltatime)/1.5f, 0);
        m_Position = pos;
    }

    m_pScene->m_pGameObjects["BossHealthbar1"]->SetHealth(m_Health);
    m_pScene->m_pGameObjects["BossHealthbar1"]->SetMaxHealth(m_MaxHealth);
}

void RedBossObject::AddLazerToScene(PlayerObject * playerobject)
{
    GameObject* LazerTemp;
    LazerTemp = m_LazerPool.GetObjectFromPool();
    LazerTemp->SetPosition(this->GetPosition());
    LazerTemp->GetPhysicsBody()->SetActive(true);
    LazerTemp->GetPhysicsBody()->SetAwake(true);
    LazerTemp->SetRenderOrder(1);
    LazerTemp->SetPosition(vec3(m_Position.x + 9.1f, m_Position.y, m_Position.z));
    ((LazerObject*)LazerTemp)->SetScene(m_pScene);
    if (m_pGame->GetIsSoundOn())
    {
        m_pGame->GetSoundPlayer()->PlaySound(m_pScene->GetResourceManager()->GetSoundObj("ProjectileShot"));
    }
    m_pScene->m_pGameObjects[LazerTemp->GetName()] = LazerTemp;
}

void RedBossObject::AddLazerToPool()
{
    for (int i = 0; i < 15; i++)
    {
        LazerObject* Lazer;
        Lazer = new LazerObject(m_pScene, "Lazer" + std::to_string(i + 50), vec3(20,20,20), vec3(0, 0, 0), vec3(18, 1, 1), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("TextureLazer"), m_pGame);
        Lazer->SetPool(&m_LazerPool);
        Lazer->AddPhysicsBox(vec2(18, 1), true, true, 1, true);
        m_LazerPool.ReturnObject(Lazer);
    }
}

void RedBossObject::AddProjectileToPool()
{
    for (int i = 0; i < 50; i++)
    {
        ProjectileObject* Projectile;
        Projectile = new ProjectileObject(m_pScene, "Projectile" + std::to_string(i + 50) , vec3(20, 20, 20), vec3(0, 0, 0), vec3(1, 1, 1), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("TextureProjectile"), m_pGame);
        Projectile->SetPool(&m_ProjectilePool);
		Projectile->SetLineMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureProjectile"));
        Projectile->AddPhysicsCircle(0.4f, true, true, 1, true);
        m_ProjectilePool.ReturnObject(Projectile);
    }
}

void RedBossObject::AddProjectileToScene(PlayerObject * playerobject, ProjectileType type)
{
    GameObject* ProjectileTemp;
    ProjectileTemp = m_ProjectilePool.GetObjectFromPool();
    ProjectileTemp->SetPosition(this->GetPosition());
    ProjectileTemp->GetPhysicsBody()->SetActive(true);
    ProjectileTemp->GetPhysicsBody()->SetAwake(true);
    ProjectileTemp->SetRenderOrder(2);
    ((ProjectileObject*)ProjectileTemp)->SetPlayer(playerobject);
    ((ProjectileObject*)ProjectileTemp)->ResetTimers();
    ((ProjectileObject*)ProjectileTemp)->SetScene(m_pScene);
    ((ProjectileObject*)ProjectileTemp)->SetType(type);
    if (m_pGame->GetIsSoundOn())
    {
        m_pGame->GetSoundPlayer()->PlaySound(m_pScene->GetResourceManager()->GetSoundObj("ProjectileShot"));
    }
    m_pScene->m_pGameObjects[ProjectileTemp->GetName()] = ProjectileTemp;
}

void RedBossObject::AddParticleToPool()
{
    for (int i = 0; i < 400; i++)
    {
        ParticleObject* Particle;
        Particle = new ParticleObject(m_pScene, "Particle" + std::to_string(i + 50), m_Position, vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("TextureRedParticle1"), m_pGame);
        Particle->SetPool(&m_ParticlePool);
        m_ParticlePool.ReturnObject(Particle);
    }
}

void RedBossObject::AddParticleToScene(ParticleType type)
{
    GameObject* ParticleTemp;
    ParticleTemp = m_ParticlePool.GetObjectFromPool();
    ParticleTemp->SetPosition(this->GetPosition());
    ParticleTemp->SetRenderOrder(4);
    ((ParticleObject*)ParticleTemp)->SetScene(m_pScene);
    ((ParticleObject*)ParticleTemp)->SetParticleType(type);

    m_pScene->m_pGameObjects[ParticleTemp->GetName()] = ParticleTemp;
}

void RedBossObject::AddMagicCircleToScene(PlayerObject * playerobject)
{
    GameObject* MagicCircletemp;
    MagicCircletemp = m_MagicCirclePool.GetObjectFromPool();
    ((MagicCircleObject*)MagicCircletemp)->ResetTimers();
    ((MagicCircleObject*)MagicCircletemp)->SetScene(m_pScene);
    MagicCircletemp->SetPosition(playerobject->GetPosition());
    MagicCircletemp->SetRenderOrder(2);
    if (m_pGame->GetIsSoundOn())
    {
        m_pGame->GetSoundPlayer()->PlaySound(m_pScene->GetResourceManager()->GetSoundObj("MagicCircle2"));
    }

    m_pScene->m_pGameObjects[MagicCircletemp->GetName()] = MagicCircletemp;

}

void RedBossObject::AddMagicCircleToPool()
{
    for (int i = 0; i < 4; i++)
    {
        MagicCircleObject* MagicCircle;
        MagicCircle = new MagicCircleObject(m_pScene, "MagicCircle" + std::to_string(i + 50), vec3(20, 20, 20), vec3(0, 0, 0), vec3(4, 4, 4), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("TextureMagicCircleRed"), m_pGame);
        MagicCircle->SetPool(&m_MagicCirclePool);
        m_MagicCirclePool.ReturnObject(MagicCircle);
    }
}


void RedBossObject::ProjectileAttack(float delta)
{
    //Setting up the projectile to shoot;
    if (m_PlayerObject != nullptr)
    {
        m_ProjectileTimer -= delta;

        if (m_ProjectileTimer <= 0)
        {
            m_ProCount++;
            AddProjectileToScene(m_PlayerObject, m_ProjectileType);
			if (m_pGame->GetDiffculty() == false)
			{
				m_ProjectileTimer = PROJECTILETIMER;
			}
			else
			{
				m_ProjectileTimer = PROJECTILETIMER + 0.3f;
			}
            m_pParticleType = ExplosiveParticle;
            for (int i = 0; i < 10; i++)
            {
                AddParticleToScene(m_pParticleType);
            }
        }
        if (m_ProCount == 10)
        {
            m_AttackDone = true;
            m_ProCount = 0;
        }
    }
}

void RedBossObject::GroundAttack(float delta)
{
    // Creates a circle, starts a timer, timer finsihes, create another circle;
    if (m_PlayerObject != nullptr)
    {
        m_MagicCircleTimer -= delta;

        if (m_MagicCircleCreated == false)
        {
            AddMagicCircleToScene(m_PlayerObject);
            m_MagicCircleCreated = true;
            m_MagicCircleTimer = MAGICCIRCLESPAWNTIMER;
            m_Count++;
        }

        if (m_MagicCircleTimer <= 0)
        {
            AddMagicCircleToScene(m_PlayerObject);
			if (m_pGame->GetDiffculty() == false)
			{
				m_MagicCircleTimer = MAGICCIRCLESPAWNTIMER;
			}
			else
			{
				m_MagicCircleTimer = MAGICCIRCLESPAWNTIMER + 0.75f;
			}
            m_Count++;
        }
        if (m_Count == 3)
        {
            m_AttackDone = true;
            m_Count = 0;
        }
    }
}

void RedBossObject::LazerAttack(float delta)
{
    //Setting up the lazer to shoot;
    if (m_PlayerObject != nullptr)
    {
        m_LazerTimer -= delta;

        if (m_LazerTimer <= 0)
        {
            m_Count++;
            AddLazerToScene(m_PlayerObject);
            m_LazerTimer = LAZERATTACKTIMER;
            m_pParticleType = ExplosiveParticle;
            for (int i = 0; i < 5; i++)
            {
                AddParticleToScene(m_pParticleType);
            }
        }
        if (m_Count == 5)
        {
            m_AttackDone = true;
            m_Count = 0;
        }
    }
}

void RedBossObject::Teleport(float delta)
{

}

void RedBossObject::Orbit(float delta)
{

}

void RedBossObject::Reset()
{
    m_Health = m_MaxHealth;
    m_AttackDone = true;

	m_Position = vec3(vec3(5, 0, 0));

    m_TestTimer = 3.0f;
    m_LazerTimer = LAZERATTACKTIMER;
    m_MagicCircleTimer = MAGICCIRCLETIMER;
    m_ProjectileTimer = PROJECTILETIMER;
    m_AttackTimer = EASYATTACKTIMER;

}

void RedBossObject::Clear(float delta)
{

}

void RedBossObject::SetPlayerObject(PlayerObject* playerobject)
{
    m_PlayerObject = playerobject;
}

void RedBossObject::ChangeHealth(int health)
{
    m_pParticleType = AnimatedParticle;
    AddParticleToScene(m_pParticleType);
    m_Health -= health;
}

RedBossObject::BossState RedBossObject::GetBossState()
{
    return RedBossObject::BossState(m_BossState);
}

void RedBossObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos, vec3 pos)
{
    if (m_pMesh == 0)
        return;

    ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

    mat4 world;
    world.CreateSRT(m_Scale, m_Rotation, m_Position);

    m_pMesh->SetupAttributes(pShaderProgram);
    m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos, m_Position);
    m_pMesh->Draw(pShaderProgram);
}

void RedBossObject::SetTeleportPosition(int node)
{
	// Sets the pos at the teleport node
    if (node = 1)
    {
        this->SetPosition(m_TeleportNode1);
    }
    if (node = 2)
    {
        this->SetPosition(m_TeleportNode2);
    }
    if (node = 3)
    {
        this->SetPosition(m_TeleportNode3);
    }
    if (node = 4)
    {
        this->SetPosition(m_TeleportNode4);
    }
    if (node = 5)
    {
        this->SetPosition(m_TeleportNode5);
    }
    if (node = 6)
    {
        this->SetPosition(m_TeleportNode6);
    }
    if (node = 7)
    {
        this->SetPosition(m_TeleportNode7);
    }
    if (node = 8)
    {
        this->SetPosition(m_TeleportNode8);
    }
    if (node = 9)
    {
        this->SetPosition(m_TeleportNode9);
    }
}

