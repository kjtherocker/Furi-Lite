#include "GamePCH.h"

DiffcultyConfirm::DiffcultyConfirm(Game* pGame, ResourceManager* pResources, Framework * pframework)
: Scene( pGame, pResources, pframework)
{
	CurrentSelection = 0;
}

DiffcultyConfirm::~DiffcultyConfirm()
{
}

void DiffcultyConfirm::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged( width, height );
}

void DiffcultyConfirm::LoadContent()
{
    Scene::LoadContent();



	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

		m_pGameObjects["DiffcultyConfirmMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, 0), vec3(0, 0, 0), vec3(15, 5, 1), "Box", "TextureEasy", m_pGame);
		m_pGameObjects["DiffcultyConfirmMenu"]->SetRenderOrder(1);
    }
}

void DiffcultyConfirm::Update(float deltatime)
{

    Scene::Update( deltatime );

	if (CurrentSelection == 0)
	{
		m_pGameObjects["DiffcultyConfirmMenu"]->SetMaterial(m_pResources->GetMaterial("TextureEasy"));
		m_pGame->SetDiffculty(0);
	}
	if (CurrentSelection == 1)
	{   
		m_pGameObjects["DiffcultyConfirmMenu"]->SetMaterial(m_pResources->GetMaterial("TextureNormal"));
		m_pGame->SetDiffculty(1);
	}
	
}

void DiffcultyConfirm::Draw()
{
    Scene::Draw();
}

void DiffcultyConfirm::OnEvent(Event * pEvent)
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
					CurrentSelection = 0;
				}
				if (pInputEvent->GetID() == VK_RIGHT)
				{
					
					CurrentSelection = 1;
				}
				if (pInputEvent->GetID() == VK_F1)
				{
					m_pGame->GetSceneManager()->PopScene();
				}

				if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
				{
					if (CurrentSelection == 0)
					{
						m_pGame->GetSceneManager()->PopScene();
						m_pGame->GetSceneManager()->PopScene();
						m_pGame->GetSceneManager()->PushScene("SampleScene");
					}
					if (CurrentSelection == 1)
					{
						m_pGame->GetSceneManager()->PopScene();
						m_pGame->GetSceneManager()->PopScene();
						m_pGame->GetSceneManager()->PushScene("SampleScene");
					}
				}
			}
		}
	}

}
