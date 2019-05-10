#include "GamePCH.h"

OptionMenuConfirm::OptionMenuConfirm(Game* pGame, ResourceManager* pResources, Framework * pframework)
    : Scene(pGame, pResources, pframework)
{
    CurrentSelection = 0;
}

OptionMenuConfirm::~OptionMenuConfirm()
{
}

void OptionMenuConfirm::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged(width, height);
}

void OptionMenuConfirm::LoadContent()
{
    Scene::LoadContent();



    // Create some game objects.
    {
        // Camera
        m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

        m_pGameObjects["OptionConfirmMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, -6), vec3(0, 0, 0), vec3(15, 5, 1), "Box", "TextureYesMenu", m_pGame);
        m_pGameObjects["OptionConfirmMenu"]->SetRenderOrder(4);





    }
}

void OptionMenuConfirm::Update(float deltatime)
{

    Scene::Update(deltatime);


}

void OptionMenuConfirm::Draw()
{
    Scene::Draw();
}

void OptionMenuConfirm::OnEvent(Event * pEvent)
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
                    m_pGameObjects["OptionConfirmMenu"]->SetMaterial(m_pResources->GetMaterial("TextureYesMenu"));
                    CurrentSelection = 0;
                }
                if (pInputEvent->GetID() == VK_RIGHT)
                {
                    m_pGameObjects["OptionConfirmMenu"]->SetMaterial(m_pResources->GetMaterial("TextureNoMenu"));
                    CurrentSelection = 1;
                }

                if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
                {
                    if (CurrentSelection == 0)
                    {
                        m_pGame->SaveSound("Data/Json/test.scene");
                        m_pGame->GetSceneManager()->PopScene();
                        m_pGame->GetSceneManager()->PopScene();
                    }
                    if (CurrentSelection == 1)
                    {
                        m_pGame->LoadSceneFile("Data/Json/test.scene");
                        m_pGame->GetSceneManager()->PopScene();
                        m_pGame->GetSceneManager()->PopScene();
                    }
                }
            }
        }
    }

}
