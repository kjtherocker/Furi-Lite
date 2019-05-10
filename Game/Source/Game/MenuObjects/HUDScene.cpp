#include "GamePCH.h"

HUDScene::HUDScene(Game* pGame, ResourceManager* pResources, Framework * pframework)
: Scene( pGame, pResources, pframework)
{
    SoundSetting = m_pGame->GetIsSoundOn();
	CurrentSelection = 0;
	ClearScoreSetting = 0;
}

HUDScene::~HUDScene()
{
	delete m_pTween;
}

void HUDScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged( width, height );
}

void HUDScene::LoadContent()
{
    Scene::LoadContent();

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -25), vec3(0, 0, 0), vec3(1, 1, 1));

		m_pGameObjects["MainMenu"] = new GameObject(this, "MainMenu", vec3(0, 0, 0), vec3(0, 0, 0), vec3(12.5f, 15, 1), "Box", "TextureOptionMenu", m_pGame);
		m_pGameObjects["MainMenu"]->SetRenderOrder(1);
    }
}

void HUDScene::Update(float deltatime)
{
    
    Scene::Update( deltatime );
	ImGui::Text("%i", CurrentSelection);
	ImGui::Text("%f", m_pTween->GetReturn());


}

void HUDScene::Draw()
{
    Scene::Draw();
}

void HUDScene::OnEvent(Event * pEvent)
{



}
