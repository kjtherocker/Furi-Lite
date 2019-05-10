#include "GamePCH.h"

BothBoss::BothBoss(Game* pGame, ResourceManager* pResources, Framework * pframework)
    : Scene(pGame, pResources, pframework)
{
    m_pSkyBoxObject = 0;
	m_WireFrameToggle = 0;
}

BothBoss::~BothBoss()
{
    delete m_pSkyBoxObject;
}

void BothBoss::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged(width, height);
}

void BothBoss::LoadContent()
{
    Scene::LoadContent();

    // Create some game objects.
    {    


		// Player
		m_pGameObjects["Player"] = new PlayerObject(this, "Player", vec3(-1.5f, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureMegaman", m_pGame);
		((PlayerObject*)m_pGameObjects["Player"])->SetController(m_pGame->GetController(0));
		((PlayerObject*)m_pGameObjects["Player"])->AddPhysicsCircle(0.4f, true, true, 0.5f, true);

		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));
		((CameraObject*)m_pGameObjects["Camera"])->SetPlayerObject(((PlayerObject*)m_pGameObjects["Player"]));

		m_pGameObjects["Score"] = new ScoreObject(this, "Score", vec3(4, -7, -2), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1), "Box", "ScoreNumbers", m_pGame);

		m_pGameObjects["Reflector"] = new GameObject(this, "Reflector", vec3(0, -3, 2), vec3(0, 0, 0), vec3(0.2f), "Sphere", "TextureSkyBoxReflection", m_pGame);

		m_pSkyBoxObject = new SkyBoxObject(this, "SkyBox", vec3(0, 0, 0), vec3(0, 90, 0), vec3(5), "Obj", "TextureSkyBox", m_pGame);


		m_pGameObjects["Ground"] = new GameObject(this, "Ground", vec3(0, 0, 7), vec3(0, 0, 0), vec3(13, 13, 1), "Obj", "TextureBlueAreanaFloor", m_pGame);
		m_pGameObjects["Ground"]->SetRenderOrder(1);

		m_pGameObjects["WallTop"] = new GameObject(this, "WallTop", vec3(0, 9, 0), vec3(0, 0, 0), vec3(10, 1, 1), "Obj", "TextureBlueArenaWall", m_pGame);
		m_pGameObjects["WallTop"]->AddPhysicsBox(vec2(25, 1), true, true, 1, false);
		m_pGameObjects["WallTop"]->SetRenderOrder(4);

		m_pGameObjects["WallBottom"] = new GameObject(this, "WallBottom", vec3(0, -9, 0), vec3(0, 0, 0), vec3(10, 1, 1), "Obj", "TextureBlueArenaWall", m_pGame);
		m_pGameObjects["WallBottom"]->AddPhysicsBox(vec2(25, 1), true, true, 1, false);
		m_pGameObjects["WallBottom"]->SetRenderOrder(4);

		m_pGameObjects["WallLeft"] = new GameObject(this, "WallLeft", vec3(-9, 0, 0), vec3(0, 0, 0), vec3(1, 8, 1), "Obj", "TextureBlueArenaWall", m_pGame);
		m_pGameObjects["WallLeft"]->AddPhysicsBox(vec2(25, 1), true, true, 1, false);
		m_pGameObjects["WallLeft"]->SetRenderOrder(4);

		m_pGameObjects["WallRight"] = new GameObject(this, "WallRight", vec3(9, 0, 0), vec3(0, 0, 0), vec3(1, 8, 1), "Obj", "TextureBlueArenaWall", m_pGame);
		m_pGameObjects["WallRight"]->AddPhysicsBox(vec2(25, 1), true, true, 1, false);
		m_pGameObjects["WallRight"]->SetRenderOrder(4);

		m_pGameObjects["BlueBossWall"] = new GameObject(this, "BlueBossWall", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Obj", "TextureBlueArenaWall", m_pGame);
		m_pGameObjects["BlueBossWall"]->SetHasPhysics(true);
		m_pGameObjects["BlueBossWall"]->AddPhysicsBox(vec2(2, 5), true, true, 1, false);
		m_pGameObjects["BlueBossWall"]->SetRenderOrder(4);

        m_pGameObjects["RedBoss"] = new RedBossObject(this, "Pickup", vec3(8, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureRedBoss", m_pGame);
        ((RedBossObject*)m_pGameObjects["RedBoss"])->SetPlayerObject(((PlayerObject*)m_pGameObjects["Player"]));
        m_pGameObjects["RedBoss"]->AddPhysicsCircle(10, true, true, 1, false);

		m_pGameObjects["BlueBoss"] = new BlueBossObject(this, "BlueBoss", vec3(8, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureBlueBoss", m_pGame);
		((BlueBossObject*)m_pGameObjects["BlueBoss"])->SetPlayerObject(((PlayerObject*)m_pGameObjects["Player"]));
		m_pGameObjects["BlueBoss"]->AddPhysicsCircle(1.0f, true, true, 1, false);
		
        m_pGameObjects["Pickup"] = new GameObject(this, "Pickup", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureTarget", m_pGame);


		m_pGameObjects["BlueBossWall"]->AddPrismaticJoint(((GameObject*)m_pGameObjects["BlueBossWall"])->GetPosition().x, ((GameObject*)m_pGameObjects["BlueBossWall"])->GetPosition().y, b2Vec2(-1.0f, 1.0f),
			m_pGameObjects["BlueBossWall"]->GetPhysicsBody(), this->GetBox2DWorld()->GetGroundBody(), true, -10, 10);

		m_Health = 50;
		truepos.Set(0, 0, 0, 0);
        MouseX = 5;
        MouseY = 5;
    }

    {
        //Lights
        int m_NumberOfLights = 5;
        vec3 m_LightColor[5] = { vec3(1, 1, 1),  vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(1,0,0) };
        vec3 m_LightPos[5] = { vec3(8, 8, -2),  vec3(-8, -8, -2), vec3(-8, 8, -2), vec3(8, -8, -2), ((RedBossObject*)m_pGameObjects["RedBoss"])->GetPosition() };
    }

    //Render Order
    // 1 - Background & Map
    // 2 - Projectiles
    // 3 - Bosses
    // 4 - Player
    {
        m_pGameObjects["Pickup"]->SetRenderOrder(4);
        m_pGameObjects["Player"]->SetRenderOrder(4);
        m_pGameObjects["RedBoss"]->SetRenderOrder(3);
    }
}

void BothBoss::OnEvent(Event * pEvent)
{

    if (pEvent->GetEventType() == EventType_RemoveFromScene)
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = (RemoveFromSceneEvent*)pEvent;

        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();
        pGameObject->RemoveFromScene();
    }

    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInputEvent = (InputEvent*)pEvent;

        if (pInputEvent->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            if (pInputEvent->GetInputState() == InputState_Pressed)
            {

                if (pInputEvent->GetID() == VK_LEFT)
                {
					m_pGameObjects["WallTop"]->GetPhysicsBody()->ApplyForce(b2Vec2(-50, 50), b2Vec2(0.0f, 0.0f), true);
                }
                if (pInputEvent->GetID() == VK_RIGHT)
                {
					m_pGameObjects["WallTop"]->GetPhysicsBody()->ApplyForce(b2Vec2(50, -50), b2Vec2(0.0f, 0.0f), true);
                }
                if (pInputEvent->GetID() == VK_F1)
                {
                    this->Reset();
                    m_pGame->GetSceneManager()->PushScene("OptionMenu");
                }
                if (pInputEvent->GetID() == VK_F2)
                {
                    Reset();
					m_pGame->GetSceneManager()->PopScene();
                    m_pGame->GetSceneManager()->PushScene("MainMenu");
                }
                if (pInputEvent->GetID() == VK_F3)
                {
                   
                        m_pGame->SetTestMode(m_TestMode =! m_TestMode);
                    
                }
                if (pInputEvent->GetID() == VK_F4)
                {
					this->Reset();
                    m_pGame->GetSceneManager()->PopScene();
                    m_pGame->GetSceneManager()->PushScene("ScoreMenu");
                }
            }
        }
    }

}

void BothBoss::Update(float deltatime)
{

    Scene::Update(deltatime);

    m_pGame->GetSceneManager()->SetRenderScene(m_pGame->GetSceneManager()->GetScene("BothBoss"));

    ((PlayerObject*)m_pGameObjects["Player"])->SetScore((ScoreObject*)m_pGameObjects["Score"]);

	m_pGame->SetPlayerScore(((ScoreObject*)m_pGameObjects["Score"])->GetScore());

	((RedBossObject*)m_pGameObjects["RedBoss"])->SetHealth(m_Health);
	((BlueBossObject*)m_pGameObjects["BlueBoss"])->SetHealth(m_Health);

	if (m_pGame->GetUserInterface() == false)
	{
		m_pGameObjects["Score"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
	}
	else
	{
		m_pGameObjects["Score"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("ScoreNumbers"));
	}

	if (m_pGame->GetTestMode())
	{
		ImGui::Begin("Debug Window", 0, 0);

		if (ImGui::Button("WireFrame"))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			m_WireFrameToggle = !m_WireFrameToggle;

			glPolygonMode(GL_FRONT_AND_BACK, (m_WireFrameToggle) ? GL_LINE : GL_FILL);

		}
		ImGui::End();
	}

    if (m_Health <= 0)
    {
		m_pGame->SetRedbosskilled(1);
		m_pGame->SaveSound("Data/Json/test.scene");
		m_pGameObjects["BlueBossWall"]->SetPosition(vec3(0, 0, 0));
		m_Health = 50;
		Reset();
        m_pGame->GetSceneManager()->PopScene();
        m_pGame->GetSceneManager()->PushScene("ScoreMenu");
    }

    m_pSkyBoxObject->Update(deltatime);
	
	if (m_pGame->GetTestMode())
	{
		m_pGameObjects["Reflector"]->SetPosition(vec3(0, -3, -3));
	}
	else
	{
		m_pGameObjects["Reflector"]->SetPosition(vec3(0, -3, 10));
	}
    // Teleporting
    ((PlayerObject*)m_pGameObjects["Player"])->SendCursorPosition(((GameObject*)m_pGameObjects["Pickup"])->GetPosition());

    //Lights
    m_LightPos[4] = ((RedBossObject*)m_pGameObjects["RedBoss"])->GetPosition();
    m_pMesh->SetLightInfo(m_NumberOfLights, m_LightPos, m_LightColor);
	vec3 lightpos = vec3(8, 8, 5);
	((RedBossObject*)m_pGameObjects["RedBoss"])->SetBossPos(lightpos);
	// Mouse
    m_pFramework->GetMouseCoordinates(&MouseX, &MouseY);
    truepos = ((CameraObject*)m_pGameObjects["Camera"])->GetTrueMouseCoord(vec2(float(MouseX), float(MouseY)));

    m_pGameObjects["Pickup"]->SetPosition(Vector3(float(truepos.x), float(truepos.y), 0.0f));

    // Shooting
    if (((PlayerObject*)m_pGameObjects["Player"])->GetIsShooting() == true)
    {
        RayCastResultCallback raycastresult;
        b2Vec2 pointa = b2Vec2(((PlayerObject*)m_pGameObjects["Player"])->GetPosition().x, ((PlayerObject*)m_pGameObjects["Player"])->GetPosition().y);
        b2Vec2 pointb = b2Vec2(float(truepos.x), float(truepos.y));
        m_pBox2DWorld->GetWorld()->RayCast(&raycastresult, pointa, pointb);

        if (raycastresult.m_Hit == true)
        {
            if (raycastresult.m_pBody->GetUserData() == m_pGameObjects["RedBoss"])
            {
				m_Health -= 5;
                ((ScoreObject*)m_pGameObjects["Score"])->AddScore(5);
				
                ((PlayerObject*)m_pGameObjects["Player"])->SetIsShooting(false);
            }
			if (raycastresult.m_pBody->GetUserData() == m_pGameObjects["BlueBoss"])
			{
				m_Health -= 5;
				((ScoreObject*)m_pGameObjects["Score"])->AddScore(5);

				((PlayerObject*)m_pGameObjects["Player"])->SetIsShooting(false);
			}
        }
    }

	
}

void BothBoss::Draw()
{

    CameraObject* pCamera = (CameraObject*)GetGameObject("Camera");

    if (pCamera)
    {
        vec3 campos = pCamera->GetPosition();
        mat4* pMatView = pCamera->GetViewMatrix();
        mat4* pMatProj = pCamera->GetProjMatrix();

        glFrontFace(GL_CCW);

        glDepthMask(GL_FALSE);

        m_pSkyBoxObject->Draw(2, pMatView, pMatProj, campos);

        glDepthMask(GL_TRUE);

        glFrontFace(GL_CW);

    }

    Scene::Draw();
}
