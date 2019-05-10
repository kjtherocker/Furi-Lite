#include "GamePCH.h"

TitleMenu::TitleMenu(Game* pGame, ResourceManager* pResources, Framework * pframework)
: Scene( pGame, pResources, pframework)
{
}

TitleMenu::~TitleMenu()
{
}

void TitleMenu::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged( width, height );
}

void TitleMenu::LoadContent()
{
    Scene::LoadContent();



	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

		m_pGameObjects["MainMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, 0), vec3(0, 0, 0), vec3(21, 21, 1), "Box", "TextureTitleMenu", m_pGame);
		m_pGameObjects["MainMenu"]->SetRenderOrder(1);





    }
}

void TitleMenu::Update(float deltatime)
{

    Scene::Update( deltatime );

	
}

void TitleMenu::Draw()
{
    Scene::Draw();
}

void TitleMenu::OnEvent(Event * pEvent)
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
					//m_pGame->GetSceneManager()->PopScene();
				}
				if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
				{
					m_pGame->GetSceneManager()->PopScene();
					m_pGame->GetSceneManager()->PushScene("MainMenu");
				}
			}
		}
	}

}
