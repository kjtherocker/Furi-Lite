#include "GamePCH.h"

PlayerObject::PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
	: GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
	m_pController = 0;
	m_MaxHealth = 300;
	m_Health = 300;
	m_HasPhysics = false;
	m_IsShooting = false;
	m_IsCollidingWithWall = false;
	m_FireTimer = 0.0f;
	m_InvincibleTimeLeft = 0.0f;
	m_CursorPosition = 0.0f;
	m_debugtimer = FIRERATE;
	m_Teleportrange = 6.0f;

	m_Speed = PLAYERSPEED;

	m_PlayerState = PlayerState_Normal;
	m_Category = PhysicsCategory_Player;
	m_Mask = PhysicsCategory_Default;

    m_PlayerMovment = PlayerMovement_Standing;

    m_Invincibility = false;
	m_DebugInvincibility = false;
    m_InvincibleTimeLeft = -0.1f;

	m_PreviousPosition = m_Position;

	m_Filter.maskBits = m_Mask ||
		PhysicsCategory_Attack ||
		PhysicsCategory_Wall;
  
    m_pScoreobject = 0;
    m_Hits = 0;

	m_pScene->m_pGameObjects["PlayerHealthbar"] = new HealthBarObject(m_pScene, "Healthbar", vec3(-4, 7.0f, -1.1f), vec3(0, 0, 0), vec3(6, 1, 1), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("HealthMegaman"),m_pGame);
}

PlayerObject::PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
	: GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
	m_pController = 0;
	m_MaxHealth = 300;
	m_Health = 300;
	m_HasPhysics = false;
	m_IsShooting = false;
	m_IsCollidingWithWall = false;
	m_FireTimer = 0.0f;
	m_InvincibleTimeLeft = 0.0f;
	m_CursorPosition = 0.0f;
	m_debugtimer = FIRERATE;
	m_Teleportrange = 6.0f;

	m_PlayerState = PlayerState_Normal;
	m_Category = PhysicsCategory_Player;
	m_Mask = PhysicsCategory_Default;

	m_Speed = PLAYERSPEED;
	m_PreviousPosition = m_Position;
    m_InvincibleTimeLeft = -0.1f;

    m_Invincibility = false;
	m_DebugInvincibility = false;

    m_PlayerMovment = PlayerMovement_Standing;

    m_pScoreobject = 0;
    m_Hits = 0;

	m_pScene->m_pGameObjects["PlayerHealthbar"] = new HealthBarObject(m_pScene, "Healthbar", vec3(-4, 7.0f, -1.1f), vec3(0, 0, 0), vec3(6, 1, 1), m_pScene->GetResourceManager()->GetMesh("Box"), m_pScene->GetResourceManager()->GetMaterial("HealthMegaman"), m_pGame);
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::SetController(PlayerController* pController)
{
	m_pController = pController;
}

void PlayerObject::Update(float deltatime)
{
	GameObject::Update(deltatime);

	m_FireTimer -= deltatime;
	m_TeleportTimer -= deltatime;

	if (m_pGame->GetUserInterface() == false)
	{
		m_pScene->m_pGameObjects["PlayerHealthbar"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
	}
	else
	{
		m_pScene->m_pGameObjects["PlayerHealthbar"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("HealthMegaman"));
	}

	if (m_pGame->GetTestMode())
	{

		ImGui::Begin("PlayerWindow", 0, 0);

		if (ImGui::Button("Immortality"))
		{
			m_DebugInvincibility = true;
		}

		
		ImGui::SliderFloat("immortalityTimer", &m_InvincibleTimeLeft, 0, 30);

		ImGui::SliderInt("Health", &m_Health, 0, m_MaxHealth);

		ImGui::SliderFloat("FireRate", &m_debugtimer, 0, 3);

		ImGui::SliderFloat("Teleport Range", &m_Teleportrange, 0, 30);

		ImGui::SliderFloat("Speed", &m_Speed, 0, 30);
		
		ImGui::End();
	}

    if (m_InvincibleTimeLeft >= 0)
    {
        m_Invincibility = true;
    }
    else if(m_InvincibleTimeLeft < 0)
    {
        m_Invincibility = false;
    }


	if (m_Position.x >= 8 )
	{
		m_IsCollidingWithWall = true;
		m_Position = m_Position + vec3(-1,0,0);
	}

	if ( m_Position.x <= -8)
	{
		m_IsCollidingWithWall = true;
		m_Position = m_Position + vec3(1.0f, 0, 0);
	}

	if ( m_Position.y >= 8)
	{
		m_IsCollidingWithWall = true;
		m_Position = m_Position + vec3(0.0, -1.0, 0);
	}

	if ( m_Position.y <= -8)
	{
		m_IsCollidingWithWall = true;
		m_Position = m_Position + vec3(0, 1.0f, 0);
	}

	if (m_IsCollidingWithWall != true)

	{
		if (m_pController == 0)
			return;


		

		b2Vec2 targetvelocity(0, 0);

		vec3 dir(0, 0, 0);

		if (m_pController->IsButtonPressed(PCB_Up))
		{
            m_PlayerMovment = PlayerMovement_Moving;
			dir.y += 1;
			targetvelocity.y = m_Speed;

		}
		if (m_pController->IsButtonPressed(PCB_Down))
		{
            m_PlayerMovment = PlayerMovement_Moving;
			dir.y -= 1;
			targetvelocity.y = -m_Speed;
		}
		if (m_pController->IsButtonPressed(PCB_Left))
		{
            m_PlayerMovment = PlayerMovement_Moving;
			dir.x -= 1;
			targetvelocity.x = -m_Speed;
		}
		if (m_pController->IsButtonPressed(PCB_Right))
		{
            m_PlayerMovment = PlayerMovement_Moving;
			dir.x += 1;
			targetvelocity.x = m_Speed;
		}

		if (m_pController->IsButtonPressed(PCB_Mouse))
		{
			m_PlayerState = PlayerState_Shooting;
		}
		if (m_pController->IsButtonPressed(PCB_MouseR))
		{
			m_PlayerState = PlayerState_Teleporting;
		}


		dir.Normalize();
		/*if (m_PlayerState == PlayerState_Normal)
		{
		m_Position += dir * speed * deltatime;
		}*/

		m_Position += dir * m_Speed * deltatime;

		if (m_InvincibleTimeLeft > 0)
			m_InvincibleTimeLeft -= deltatime;


		if (m_PlayerState == PlayerState_Shooting)
		{
			if (m_FireTimer <= 0)
			{
				m_IsShooting = true;

				m_FireTimer = m_debugtimer;
				m_PlayerState = PlayerState_Normal;
			}
			else if (m_FireTimer > 0)
			{
				m_IsShooting = false;
				m_PlayerState = PlayerState_Normal;
			}

		}
		if (m_PlayerState == PlayerState_Teleporting)
		{
			if (m_TeleportTimer <= 0)
			{
				m_TeleportTimer = TELEPORTTIMER;
				float distance = ((float)sqrt(pow((m_Position.x - m_CursorPosition.x), 2) + pow((m_Position.y - m_CursorPosition.y), 2)));

				if (distance <= m_Teleportrange)
				{
					m_Position = m_CursorPosition;
				}
				else
				{
					//vec3 NewPosition = m_Position * (6 / m_Distance) + m_CursorPosition * (abs(6 - m_Distance) / m_Distance);

					float x = abs(m_Position.x - m_CursorPosition.x);
					float y = abs(m_Position.y - m_CursorPosition.y);

					float angle = ((float)asin(y / distance));
					float angle1 = ((float)acos(x / distance));

					float YPos = ((float)sin(angle) * 6);
					float XPos = ((float)cos(angle1) * 6);

					// - -
					if (m_Position.x > m_CursorPosition.x && m_Position.y > m_CursorPosition.y)
					{
						m_Position = vec3(m_Position.x - XPos, m_Position.y - YPos, m_Position.z);
					}
					// + +
					if (m_Position.x < m_CursorPosition.x && m_Position.y < m_CursorPosition.y)
					{
						m_Position = vec3(m_Position.x + XPos, m_Position.y + YPos, m_Position.z);
					}

					if (m_Position.x > m_CursorPosition.x && m_Position.y < m_CursorPosition.y)
					{
						m_Position = vec3(m_Position.x - XPos, m_Position.y + YPos, m_Position.z);
					}
					if (m_Position.x < m_CursorPosition.x && m_Position.y > m_CursorPosition.y)
					{
						m_Position = vec3(m_Position.x + XPos, m_Position.y - YPos, m_Position.z);
					}
				}
			}
			m_PlayerState = PlayerState_Normal;
		}
		if (m_PlayerState == PlayerState_Cutscene)
		{
		}

        if (m_PreviousPosition == m_Position)
        {
            m_PlayerMovment = PlayerMovement_Standing;
        }

		m_PreviousPosition = m_Position;
	}
	else
	{
		m_IsCollidingWithWall = false;
	}

    if (m_Health <= 0)
    {
        m_pScene->Reset();
    }

    m_pGame->SetPlayerHits(m_Hits);
   

	m_pScene->m_pGameObjects["PlayerHealthbar"]->SetHealth(m_Health);
    m_pScene->m_pGameObjects["PlayerHealthbar"]->SetMaxHealth(m_MaxHealth);


}

void PlayerObject::BeginContact(b2Fixture * pOtherFixture, vec2 worldPosition, vec2 worldNormal)
{
	GameObject::BeginContact(pOtherFixture, worldPosition, worldNormal);

	GameObject * collidedwith = (GameObject*)pOtherFixture->GetBody()->GetUserData();

	std::string m_name = collidedwith->GetName();

	if (m_name.compare(0, 22, "MagicPillarMagicCircle") == 0)
	{
		
            
		if (m_DebugInvincibility != true)
		{
			m_Health -= 10;
			m_InvincibleTimeLeft = PLAYERINVINCIBILITY;
            m_Hits++;
		}
		
	}

	if (m_name.compare(0, 10, "Projectile") == 0)
	{
        if (m_Invincibility != true)
        {
			if (m_DebugInvincibility != true)
			{
				m_Health -= 10;
				m_InvincibleTimeLeft = PLAYERINVINCIBILITY;
                m_Hits++;

			}
        }
	}

	if (m_name.compare(0, 14, "BlueProjectile") == 0)
	{
		if (m_Invincibility != true)
		{
			if (m_DebugInvincibility != true)
			{
				if (m_PlayerMovment != PlayerMovement_Standing)
				{
					m_Health -= 10;
					m_InvincibleTimeLeft = PLAYERINVINCIBILITY;
					m_Hits++;
				}
			}
		}
	}
	

    if (m_name.compare(0, 12, "BlueBossWall") == 0)
    {
        if (m_Invincibility != true)
        {
			if (m_DebugInvincibility != true)
			{
				m_Health -= 10;
				m_InvincibleTimeLeft = PLAYERINVINCIBILITY;
				m_Hits++;
			}
        }
    }

	if (m_name.compare(0, 5, "Lazer") == 0)
	{
		if (m_Invincibility != true)
		{
			if (m_DebugInvincibility != true)
			{
				m_Health -= 30;
				m_InvincibleTimeLeft = PLAYERINVINCIBILITY;
				m_Hits++;
			}
		}
	}

}

bool PlayerObject::GetIsShooting()
{
	return m_IsShooting;
}

void PlayerObject::Reset()
{
    m_PlayerState = PlayerState_Normal;

    m_Health = m_MaxHealth;

	m_DebugInvincibility = false;

    m_FireTimer = FIRERATE;

    m_TeleportTimer = TELEPORTTIMER;

    SetPosition(vec3(-1.5f, 0, 0));

}

void PlayerObject::SetIsShooting(bool isshooting)
{
	m_IsShooting = isshooting;
}

void PlayerObject::SendCursorPosition(vec3 pos)
{
	m_CursorPosition = pos;
}

