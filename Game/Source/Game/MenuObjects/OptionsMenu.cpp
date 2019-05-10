#include "GamePCH.h"

OptionMenu::OptionMenu(Game* pGame, ResourceManager* pResources, Framework * pframework)
: Scene( pGame, pResources, pframework)
{
    SoundSetting = m_pGame->GetIsSoundOn();
	CurrentSelection = 0;
	ClearScoreSetting = m_pGame->GetUserInterface();
}

OptionMenu::~OptionMenu()
{
	delete m_pTween;
}

void OptionMenu::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged( width, height );
}

void OptionMenu::LoadContent()
{
    Scene::LoadContent();

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

		m_pGameObjects["MainMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, -6), vec3(0, 0, 0), vec3(12.5f, 15, 1), "Box", "TextureOptionMenu", m_pGame);
		m_pGameObjects["MainMenu"]->SetRenderOrder(3);

		m_pGameObjects["SoundSettings"] = new GameObject(this, "SoundSettings", vec3(3, 3, -6), vec3(0, 0, 0), vec3(2, 2, 1), "Box", "TextureOFF", m_pGame);
		m_pGameObjects["SoundSettings"]->SetRenderOrder(4);

        m_pGameObjects["ClearScore"] = new GameObject(this, "ClearScore", vec3(-2, -1, -6), vec3(0, 0, 0), vec3(6, 2, 1), "Box", "TextureClearScore", m_pGame);
        m_pGameObjects["ClearScore"]->SetRenderOrder(4);

        m_pGameObjects["ClearSettings"] = new GameObject(this, "ClearSettings", vec3(3, -1, -6), vec3(0, 0, 0), vec3(2, 2, 1), "Box", "TextureOFF", m_pGame);
        m_pGameObjects["ClearSettings"]->SetRenderOrder(4);

		m_pGameObjects["SoundText"] = new GameObject(this, "SoundText", vec3(-3, 3, -6), vec3(0, 0, 0), vec3(4, 2, 1), "Box", "TextureSound", m_pGame);
		m_pGameObjects["SoundText"]->SetRenderOrder(4);

		m_pGameObjects["Cursor"] = new GameObject(this, "Cursor", m_Button1, vec3(0, 0, -6), vec3(1.5, 1.5, 1), "Box", "TextureArrow", m_pGame);
		m_pGameObjects["Cursor"]->SetRenderOrder(4);

		m_pGameObjects["Confirm"] = new GameObject(this, "Confirm", vec3(0, -6, -6), vec3(0, 0, 0), vec3(4, 2, 1), "Box", "TextureConfirm", m_pGame);
		m_pGameObjects["Confirm"]->SetRenderOrder(4);

		m_Button1 = vec3(5.3f, 3.0, -7);
		m_Button2 = vec3(5.3f, -1.0f, -7);
		m_Button3 = vec3(5.3f, -6.0f, -7);
		CurrentSelection = 1;
		m_TimePassed = 0.0f;
		m_Goal = 0.0f;
		m_Up = false;
		m_pTween = new Tween(0.0f, 0.0f, 0.0, 0.0, TweenTypeLinear);
		m_Tween = false;
		((GameObject*)m_pGameObjects["Cursor"])->SetPosition(m_Button1);
    }
}

void OptionMenu::Update(float deltatime)
{
    
    Scene::Update( deltatime );
	if (m_pGame->GetTestMode())
	{
		ImGui::Text("%i", CurrentSelection);
		ImGui::Text("%f", m_pTween->GetReturn());
	}

	if (SoundSetting == 0)
	{
		m_pGame->SetIsSoundOn(0);

		m_pGameObjects["SoundSettings"]->SetMaterial(m_pResources->GetMaterial("TextureOFF"));
	}
	if (SoundSetting == 1)
	{
		m_pGame->SetIsSoundOn(1);
		
		m_pGameObjects["SoundSettings"]->SetMaterial(m_pResources->GetMaterial("TextureON"));
	}



	if (CurrentSelection < 1)
	{
		m_Up = true;
		CurrentSelection = 3;
	}
	if (CurrentSelection > 3)
	{
		m_Up = true;
		CurrentSelection = 1;
	}

	if (m_Tween == true)
	{
		m_TimePassed += deltatime;
		
		if (m_Up == true)
		{
			if (CurrentSelection == 1)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().y, m_Button1.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button1.y;
			}

			if (CurrentSelection == 2)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().y, m_Button2.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button2.y;
			}

			if (CurrentSelection == 3)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().y, m_Button3.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button3.y;
			}
		}
		if (m_Up == false)
		{
			if (CurrentSelection == 1)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().y, m_Button1.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button1.y;
			}

			if (CurrentSelection == 2)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().y, -m_Button2.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button2.y + 1;
			}
			if (CurrentSelection == 3)
			{
				m_pTween->SetupTween(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().y, -m_Button3.y, m_TimePassed, 10.0f, TweenTypeLinear);
				m_Goal = m_Button3.y;
			}
		}
		
		m_pTween->Update(deltatime);

		if (int(m_pTween->GetReturn()) == int(m_Goal))
		{
			m_Tween = false;
			m_TimePassed = 0.0f;
		}
		((GameObject*)m_pGameObjects["Cursor"])->SetPosition(vec3(((GameObject*)m_pGameObjects["Cursor"])->GetPosition().x, m_pTween->GetReturn(), ((GameObject*)m_pGameObjects["Cursor"])->GetPosition().z));
	}

	if (ClearScoreSetting == 0)
	{
		m_pGame->SetUserInterface(0);
		m_pGameObjects["ClearSettings"]->SetMaterial(m_pResources->GetMaterial("TextureOFF"));
	}
	if (ClearScoreSetting == 1)
	{
		m_pGame->SetUserInterface(1);
		m_pGameObjects["ClearSettings"]->SetMaterial(m_pResources->GetMaterial("TextureON"));
	}

}

void OptionMenu::Draw()
{
    Scene::Draw();
}

void OptionMenu::OnEvent(Event * pEvent)
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

				if (pInputEvent->GetID() == VK_DOWN)
				{
					m_Tween = true;
					CurrentSelection++;	
					m_Up = true;
				}
				if (pInputEvent->GetID() == VK_UP)
				{
					m_Tween = true;
					CurrentSelection--;
					m_Up = false;
				}
                if (pInputEvent->GetID() == VK_F1)
                {
                    m_pGame->GetSceneManager()->PopScene();
                }

				if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
				{
					if (CurrentSelection == 1)
					{
					
						SoundSetting =! SoundSetting;
					}
					if (CurrentSelection == 2)
					{
                       
						ClearScoreSetting =! ClearScoreSetting;
					}
                    if (CurrentSelection == 3)
                    {
                        
                        
                        m_pGame->GetSceneManager()->PushScene("OptionMenuConfirm");
                    }
				}
			}
		}
	}

}
