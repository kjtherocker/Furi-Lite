#include "GamePCH.h"

MainMenuScene::MainMenuScene(Game* pGame, ResourceManager* pResources, Framework * pframework)
	: Scene(pGame, pResources, pframework)
{
}

MainMenuScene::~MainMenuScene()
{
	delete m_pTween;
}

void MainMenuScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void MainMenuScene::LoadContent()
{
	Scene::LoadContent();

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));


		//(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
		


		m_pGameObjects["MainMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, 0), vec3(0, 0, 0), vec3(21, 21, 1), "Box", "TextureMainMenu", m_pGame);
		m_pGameObjects["MainMenu"]->SetRenderOrder(1);

		m_pGameObjects["Selector"] = new GameObject(this, "Selector", vec3(0, 2, 0), vec3(0, 0, 0), vec3(3, 2, 1), "Box", "TextureArrow", m_pGame);
		m_pGameObjects["Selector"]->SetRenderOrder(2);

		m_pGameObjects["Prompt"] = new GameObject(this, "Prompt", vec3(5, -9, 0), vec3(0, 0, 0), vec3(10, 1, 1), "Box", "TextureAzureKnightPrompt", m_pGame);
		m_pGameObjects["Prompt"]->SetRenderOrder(3);

		m_pGameObjects["BossTexture"] = new GameObject(this, "BossTexture", vec3(7, -4, 0), vec3(0, 0, 0), vec3(8, 8, 1), "Box", "TextureRedBoss", m_pGame);
		m_pGameObjects["BossTexture"]->SetRenderOrder(2);

	}

	 m_pGame->LoadSceneFile("Data/Json/test.scene");

	// Cursor Positions for the buttons
	m_Button1 = vec3(0, 3.0, 0);
	m_Button2 = vec3(0, -1.0f, 0);
	m_Button3 = vec3(0, -4.0f, 0);
	m_Button4 = vec3(0, -8.0f, 0);
	m_CurrentButton = 1;
	m_TimePassed = 0.0f;
	m_Goal = 0.0f;
	m_Up = false;
	m_pTween = new Tween(0.0f, 0.0f, 0.0, 0.0, TweenTypeLinear);
	m_Tween = false;
	((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button1);
}

void MainMenuScene::Update(float deltatime)
{

	Scene::Update(deltatime);

	if (m_pGame->GetBlueBossKilled() == true && m_pGame->GetRedBossKilled() == true)
	{
		m_pGameObjects["MainMenu"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureMainMenuComplete"));
	}

	if (m_CurrentButton > 4)
	{
		m_Up = true;
		m_CurrentButton = 1;
	}
	if (m_CurrentButton < 1)
	{
		m_Up = true;
		m_CurrentButton = 4;
	}

	if (m_Tween == true)
	{
		m_TimePassed += deltatime;
		if (m_Up == true)
		{
			if (m_CurrentButton == 1)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, m_Button1.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button1.y;
			}
			if (m_CurrentButton == 2)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, m_Button2.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button2.y;
			}
			if (m_CurrentButton == 3)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, m_Button3.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button3.y;
			}
			if (m_CurrentButton == 4)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, m_Button4.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button4.y + 1;
			}
		}
		if (m_Up == false)
		{
			if (m_CurrentButton == 1)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, m_Button1.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button1.y;
			}
			if (m_CurrentButton == 2)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, -m_Button2.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button2.y + 1;
			}
			if (m_CurrentButton == 3)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, -m_Button3.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button3.y + 1;
			}
			if (m_CurrentButton == 4)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Selector"])->GetPosition().y, -m_Button4.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button4.y + 1;
			}
		}
		m_pTween->Update(deltatime);

		if ( int(m_pTween->GetReturn()) == int(m_Goal))
		{
			m_Tween = false;
			m_TimePassed = 0.0f;
		}
		((GameObject*)m_pGameObjects["Selector"])->SetPosition(vec3(((GameObject*)m_pGameObjects["Selector"])->GetPosition().x, m_pTween->GetReturn(), ((GameObject*)m_pGameObjects["Selector"])->GetPosition().z));
	}
	if (m_CurrentButton == 1)
	{
		//((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button1);
		m_pGameObjects["Prompt"]->SetMaterial(m_pResources->GetMaterial("TextureCrimsonKnightPrompt"));
		m_pGameObjects["BossTexture"]->SetMaterial(m_pResources->GetMaterial("TextureRedBoss"));
	}
	if (m_CurrentButton == 2)
	{
		//((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button2);
		m_pGameObjects["Prompt"]->SetMaterial(m_pResources->GetMaterial("TextureAzureKnightPrompt"));
		m_pGameObjects["BossTexture"]->SetMaterial(m_pResources->GetMaterial("TextureBlueBoss"));
	}
	if (m_CurrentButton == 3)
	{
		//((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button3);
		m_pGameObjects["Prompt"]->SetMaterial(m_pResources->GetMaterial("TextureBothPrompt"));
		m_pGameObjects["BossTexture"]->SetMaterial(m_pResources->GetMaterial("TextureBothBosses"));
	}
	if (m_CurrentButton == 4)
	{
		//((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button4);
		m_pGameObjects["Prompt"]->SetMaterial(m_pResources->GetMaterial("TextureOptionsPrompt"));
	}

}

void MainMenuScene::Draw()
{
	Scene::Draw();
}

void MainMenuScene::OnEvent(Event * pEvent)
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

				if (pInputEvent->GetID() == VK_UP)
				{
					m_TimePassed = 0.0f;
					m_Tween = true;
					m_CurrentButton--;
					m_Up = false;
				}

				if (pInputEvent->GetID() == VK_DOWN)
				{
					m_TimePassed = 0.0f;
					m_Tween = true;
					m_CurrentButton++;
					m_Up = true;
				}

				if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
				{
					if (m_CurrentButton == 1)
					{
						m_pGame->GetSceneManager()->PushScene("DiffcultyConfirm");
					}
					if (m_CurrentButton == 2)
					{
                        m_pGame->GetSceneManager()->PopScene();
						m_pGame->GetSceneManager()->PushScene("BlueBoss");
					}
                    if (m_CurrentButton == 3)
                    {
						if (m_pGame->GetBlueBossKilled() == true && m_pGame->GetRedBossKilled() == true)
						{
							m_pGame->GetSceneManager()->PopScene();
							m_pGame->GetSceneManager()->PushScene("BothBoss");
						}
                    }
					if (m_CurrentButton == 4)
					{
						m_pGame->GetSceneManager()->PushScene("OptionMenu");
					}
				}
			}
		}
	}

}
