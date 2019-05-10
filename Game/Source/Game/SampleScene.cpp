#include "GamePCH.h"

SampleScene::SampleScene(Game* pGame, ResourceManager* pResources, Framework * pframework)
: Scene( pGame, pResources, pframework)
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged( width, height );
}

void SampleScene::LoadContent()
{
    Scene::LoadContent();



   

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

       //m_pGameObjects["Cube"] = new GameObject(this, "Cube", vec3(0, 0, 0), vec3(0, 0, 0), vec3(5, 5, 5), "Cube", "FBOTexture");
  
       //m_pGameObjects["Lighting"] = new GameObject(this, "Lighting", vec3(-3, -3, -3), vec3(0, 0, 0), vec3(10, 10, 1), "Box", "LightingMegaman");
       //m_pGameObjects["Lighting"]->SetRenderOrder(1);
        // Player
		m_pGameObjects["Player"] = new PlayerObject(this, "Player", vec3(-1.5f, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureMegaman");
		((PlayerObject*)m_pGameObjects["Player"])->SetController(m_pGame->GetController(0));
        ((PlayerObject*)m_pGameObjects["Player"])->AddPhysicsCircle(1.0f, true, true, 0.5f, true);       

        m_pGameObjects["WallTop"] = new GameObject(this, "WallTop", vec3(0,5,0), vec3(0, 0, 0), vec3(25, 1, 1), "Box", "TextureCrate");
        m_pGameObjects["WallTop"]->AddPhysicsBox(vec2(25, 1), true, true, 1, false);
        m_pGameObjects["WallTop"]->SetRenderOrder(4);
	
      
        m_pGameObjects["RedBoss"] = new RedBossObject(this, "Pickup", vec3(8, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureRedBoss");
		((RedBossObject*)m_pGameObjects["RedBoss"])->SetPlayerObject(((PlayerObject*)m_pGameObjects["Player"]));
        m_pGameObjects["RedBoss"]->AddPhysicsCircle(1.0f, true, true, 1, false);


        m_pGameObjects["Pickup"] = new GameObject(this, "Pickup", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "TextureTarget");

		truepos.Set(0, 0, 0, 0);
       

		

		m_pGameObjects["WallTop"]->AddPrismaticJoint(((GameObject*)m_pGameObjects["WallTop"])->GetPosition().x, ((GameObject*)m_pGameObjects["WallTop"])->GetPosition().y,b2Vec2(0.0f,-1.0f),
			m_pGameObjects["WallTop"]->GetPhysicsBody(), this->GetBox2DWorld()->GetGroundBody(), true,-2,0);

        SaveSound("Data/Json/test.scene");
		   /* FILE* filehandle;
		    errno_t error = fopen_s(&filehandle,"Data/Json/test.scene","wb");
		    if (filehandle)
           		    {
	
		    	cJSON* jRoot = cJSON_CreateObject();
		    	char* jsonstr = cJSON_Print(jRoot);
		    	fwrite(jsonstr, 4, 1, filehandle);
		    	

		    	cJSON* jPlayer = cJSON_CreateObject();
		    	cJSON_AddNumberToObject(jRoot, "Score", 1234);
		    	cJSON_AddNumberToObject(jRoot, "Sound", 0);

		    	cJSON_AddItemToObject(jRoot, "GameObjects", jPlayer);
		    	fclose(filehandle);
		    	free(jsonstr);
		    }*/
		LoadSceneFile("Data/Json/test.scene");

		MouseX = 5;
		MouseY = 5;
	}

    //Render Order
    // 1 - Background & Map
    // 2 - Projectiles
    // 3 - Bosses
    // 4 - Player
    {

        m_pGameObjects["Player"]->SetRenderOrder(4);
        m_pGameObjects["RedBoss"]->SetRenderOrder(3);
    }
}

void SampleScene::OnEvent(Event * pEvent)
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
				}
				if (pInputEvent->GetID() == VK_RIGHT)
				{

				}
			}
		}
	}



}

void SampleScene::Update(float deltatime)
{

    Scene::Update( deltatime );

	m_pGameObjects["WallTop"]->GetPhysicsBody()->ApplyForce(b2Vec2(0, 0), b2Vec2(0.0f, 0.0f), true);

	m_pFramework->GetMouseCoordinates(&MouseX, &MouseY);

	truepos = ((CameraObject*)m_pGameObjects["Camera"])->GetTrueMouseCoord(vec2(float(MouseX),float(MouseY)));

 


	m_pGameObjects["Pickup"]->SetPosition(Vector3(float(truepos.x),float(truepos.y), 1.0f));

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
				((RedBossObject*)m_pGameObjects["RedBoss"])->ChangeHealth(3);
				((PlayerObject*)m_pGameObjects["Player"])->SetIsShooting(false);
            }
        }
    }

	// Teleporting
//	((PlayerObject*)m_pGameObjects["Player"])->SendCursorPosition(((GameObject*)m_pGameObjects["Pickup"])->GetPosition());
}

void SampleScene::Draw()
{
    Scene::Draw();
}
