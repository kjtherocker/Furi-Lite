#include "GamePCH.h"

MainMenuScene::MainMenuScene(Game* pGame, ResourceManager* pResources, Framework * pframework)
: Scene( pGame, pResources, pframework)
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged( width, height );
}

void MainMenuScene::LoadContent()
{
    Scene::LoadContent();

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

		m_pGameObjects["MainMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, 0), vec3(0, 0, 0), vec3(21, 21, 1), "Box", "TextureMainMenu");
		m_pGameObjects["MainMenu"]->SetRenderOrder(1);

        m_pGameObjects["Selector"] = new GameObject(this, "Selector", vec3(0, 2, 0), vec3(0, 0, 0), vec3(3, 2, 1), "Box", "TextureArrow");
        m_pGameObjects["Selector"]->SetRenderOrder(2);
    }


    // Cursor Positions for the buttons
    m_Button1 = vec3(0, 3.5, 0);
    m_Button2 = vec3(0, 0, 0);
    m_Button3 = vec3(0, -3.5, 0);
    m_Button4 = vec3(0, -7, 0);
    m_CurrentButton = 1;
}

void MainMenuScene::Update(float deltatime)
{

    Scene::Update( deltatime );

    if (m_CurrentButton > 4)
    {
        m_CurrentButton = 1;
    }
    if (m_CurrentButton < 1)
    {
        m_CurrentButton = 4;
    }

    if (m_CurrentButton == 1)
    {
        ((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button1);
    }
    if (m_CurrentButton == 2)
    {
        ((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button2);
    }
    if (m_CurrentButton == 3)
    {
        ((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button3);
    }
    if (m_CurrentButton == 4)
    {
        ((GameObject*)m_pGameObjects["Selector"])->SetPosition(m_Button4);
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
                    m_CurrentButton--;
				}

                if (pInputEvent->GetID() == VK_DOWN)
                {
                    m_CurrentButton++;
                }

				if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_EXECUTE)
				{
					m_pGame->GetSceneManager()->PopScene();
					m_pGame->GetSceneManager()->PushScene("SampleScene");
				}
			}
		}
	}

}
