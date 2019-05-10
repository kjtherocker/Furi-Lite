#include "GamePCH.h"



SceneManager::SceneManager()
{

	m_RenderScene = 0;
}

SceneManager::~SceneManager()
{
    for (auto object : m_pSceneObject )
    {
        if (object.second != nullptr)
        {
            for (int i = 0; i < (int)m_ActiveScenes.size(); i++)
            {
                if (m_ActiveScenes.at(i) == object.second)
                {
                    m_ActiveScenes.at(i) = nullptr;
                }
            }
            delete object.second;
        }
    }

    m_pSceneObject.clear();


    for (int i = 0; i < (int)m_ActiveScenes.size(); i++)
    {
        if (m_ActiveScenes.at(i) != nullptr)
        {
            delete  m_ActiveScenes.at(i);
        }
    }
    m_ActiveScenes.clear();


}

void SceneManager::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    
}

void SceneManager::LoadContent()
{

   for (auto object : m_pSceneObject)
            object.second->LoadContent();


}

void SceneManager::OnEvent(Event * pEvent)
{
	if (m_ActiveScenes.size() > 0)
	{
		m_ActiveScenes.back()->OnEvent(pEvent);
	}
}

void SceneManager::Update(float deltatime)
{
	if (m_ActiveScenes.size() > 0)
	{
        m_ActiveScenes.back()->Update(deltatime);
	}
//	m_RenderScene->Update(deltatime);
}

void SceneManager::Draw()
{
	for (int i = 0; i < (int)m_ActiveScenes.size(); i++)
	{
		m_ActiveScenes.at(i)->Draw();
	}

}

void SceneManager::PushScene(std::string name)
{
    m_ActiveScenes.push_back(((Scene*)GetScene(name)));

}

void SceneManager::PopScene()
{
    m_ActiveScenes.pop_back();
}


