#include "GamePCH.h"

ScoreMenu::ScoreMenu(Game* pGame, ResourceManager* pResources, Framework * pframework)
    : Scene(pGame, pResources, pframework)
{
    CurrentSelection = 0;
	m_Differencescore = 0;
}

ScoreMenu::~ScoreMenu()
{
    delete m_pSkyBoxObject;
}

void ScoreMenu::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged(width, height);
}

void ScoreMenu::LoadContent()
{
    Scene::LoadContent();



    // Create some game objects.
    {
        // Camera
        m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

        m_pSkyBoxObject = new SkyBoxObject(this, "SkyBox", vec3(0, 0, 0), vec3(0, 90, 0), vec3(5), "Obj", "TextureSkyBox", m_pGame);

        m_pGameObjects["HighScore"] = new ScoreObject(this, "HighScore", vec3(2, -1.5f, -7), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1), "Box", "TextureInvisible", m_pGame);
        m_pGameObjects["HighScore"]->SetRenderOrder(4);

		m_pGameObjects["HitScore"] = new ScoreObject(this, "HitScore", vec3(2, 2.7f, -7), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1), "Box", "TextureInvisible", m_pGame);
		m_pGameObjects["HitScore"]->SetRenderOrder(4);

		m_pGameObjects["PlayerScore"] = new ScoreObject(this, "PlayerScore", vec3(2, 0.5f, -7), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1), "Box", "TextureInvisible", m_pGame);
		m_pGameObjects["PlayerScore"]->SetRenderOrder(4);

		m_pGameObjects["DifferenceScore"] = new ScoreObject(this, "DifferenceScore", vec3(2, -3.5f, -7), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1), "Box", "TextureInvisible", m_pGame);
		m_pGameObjects["DifferenceScore"]->SetRenderOrder(4);

        m_pGameObjects["FBos"] = new FBOmenu(this, "FBO", vec3(-16, -10, 3), vec3(90, 0, 0), vec3(5, 40, 1), "Plane", "FBOTexture", m_pGame);
        ((FBOmenu*)m_pGameObjects["FBos"])->SetLifeTime(0.0f);

        m_pGameObjects["OptionConfirmMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, -6), vec3(0, 0, 0), vec3(13, 12, 1), "Box", "TextureInvisible", m_pGame);


    }
}

void ScoreMenu::Update(float deltatime)
{

    m_pSkyBoxObject->Update(deltatime);
    Scene::Update(deltatime);
	((ScoreObject*)m_pGameObjects["HitScore"])->SetScore(m_pGame->GetPlayerHits());

    ((ScoreObject*)m_pGameObjects["HighScore"])->SetScore(m_pGame->GetScore());

	((ScoreObject*)m_pGameObjects["PlayerScore"])->SetScore(m_pGame->GetPlayerScore());

	m_Differencescore = m_pGame->GetPlayerScore() - m_pGame->GetScore();
	((ScoreObject*)m_pGameObjects["DifferenceScore"])->SetScore(abs(m_Differencescore));

    if (m_pGameObjects["FBos"]->GetMaterial() == m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"))
    {
        m_pGameObjects["OptionConfirmMenu"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureScoreMenu"));
        m_pGameObjects["HighScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("ScoreNumbers"));
		m_pGameObjects["HitScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("ScoreNumbers"));
		m_pGameObjects["PlayerScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("ScoreNumbers"));
		m_pGameObjects["DifferenceScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("ScoreNumbers"));
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

}

void ScoreMenu::Draw()
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

void ScoreMenu::OnEvent(Event * pEvent)
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
                if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
                {
                    if (CurrentSelection == 0)
                    {
                       
                    }
                    if (CurrentSelection == 1)
                    {
                        
                    }
                    if (pInputEvent->GetID() == VK_F3)
                    {
                        
                        bool test = m_pGame->GetTestMode();

                        m_pGame->SetTestMode(test = ! test);

                    }
					if (pInputEvent->GetID() == VK_SPACE || pInputEvent->GetID() == VK_RETURN)
					{
						if (m_pGame->GetPlayerScore() > m_pGame->GetScore())
						{
							m_pGame->SetScore(m_pGame->GetPlayerScore());
							m_pGame->SaveSound("Data/Json/test.scene");
						}

						
						Reset();
						m_pGameObjects["FBos"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("FBOTexture"));
						m_pGameObjects["OptionConfirmMenu"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("FBOTexture"));
						m_pGameObjects["HighScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
						m_pGameObjects["HitScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
						m_pGameObjects["PlayerScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
						m_pGameObjects["DifferenceScore"]->SetMaterial(m_pGame->GetResourceManager()->GetMaterial("TextureInvisible"));
					    m_pGame->GetSceneManager()->PopScene();
						m_pGame->GetSceneManager()->PushScene("MainMenu");
					}
                }
            }
        }
    }

}
