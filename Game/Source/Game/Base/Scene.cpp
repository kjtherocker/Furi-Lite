#include "GamePCH.h"

Scene::Scene(Game* pGame, ResourceManager* pResources, Framework * pframework)
{
    m_pGame = pGame;
    m_pResources = pResources;

	m_pFramework = pframework;

    m_pBox2DWorld = 0;
	

}

Scene::~Scene()
{
    for( auto object: m_pGameObjects )
    {
        delete object.second;
    }
	
}

void Scene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
}

void Scene::LoadContent()
{
    m_pBox2DWorld = m_pGame->GetWorld();


   


}

void Scene::Reset()
{
    // reset all of the Scene objects in the list.
    for( auto it = m_pGameObjects.cbegin(); it != m_pGameObjects.cend(); )
    {
        auto object = it;
        it++; // pre-increment the iterator, so if this object is removed we already know the next one

        object->second->Reset();
    }
}

void Scene::OnEvent(Event* pEvent)
{
    if( pEvent->GetEventType() == EventType_RemoveFromScene )
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = (RemoveFromSceneEvent*)pEvent;

        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();
        pGameObject->RemoveFromScene();
    }

    if( pEvent->GetEventType() == EventType_Input )
    {
        InputEvent* pInputEvent = (InputEvent*)pEvent;

        if( pInputEvent->GetInputDeviceType() == InputDeviceType_Keyboard &&
            pInputEvent->GetInputState() == InputState_Pressed &&
            pInputEvent->GetID() == 'R' )
        {
            Reset();
        }
    }
}

void Scene::Update(float deltatime)
{
    CheckForGLErrors();

    // Update all of the Scene objects in the list.
    for( auto object: m_pGameObjects )
    {
        object.second->Update( deltatime );
    }

    CheckForGLErrors();
}

void Scene::Draw()
{
    CheckForGLErrors();

	CameraObject* pCamera = (CameraObject*)GetGameObject("Camera");

	if( pCamera )
	{
		vec3 campos = pCamera->GetPosition();
		mat4* pMatView = pCamera->GetViewMatrix();
		mat4* pMatProj = pCamera->GetProjMatrix();

		// Render all of the Scene objects in the list.
		for( int i=0; i<5; i++ )
		{
            //for( std::map<std::string, GameObject*>::iterator iterator = m_pGameObjects.begin(); iterator != m_pGameObjects.end(); iterator++ )
            for( auto object: m_pGameObjects )
            {
                if( object.second->GetRenderOrder() == i )
                {
                    object.second->Draw( i, pMatView, pMatProj, campos );
                }
            }
		}
	}

    CheckForGLErrors();
}

void Scene::AddToScene(std::string name, GameObject* object)
{
    object->SetScene( this );
    m_pGameObjects[name] = object;
}

void Scene::RemoveFromScene(GameObject* object)
{
    m_pGameObjects.erase( object->GetName() );
}

