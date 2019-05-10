#ifndef __Scene_H__
#define __Scene_H__

class Game;
class GameObject;

class Scene
{
protected:
    Game* m_pGame;
    ResourceManager* m_pResources;

	Box2DWorld* m_pBox2DWorld;


	Framework * m_pFramework;

private:
	

public:
    Scene(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~Scene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Reset();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

    Box2DWorld* GetBox2DWorld() { return m_pBox2DWorld; }
    GameObject* GetGameObject(const char* name) { return m_pGameObjects[name]; }
    GameObject* GetGameObject(std::string name) { return m_pGameObjects[name]; }

    void AddToScene(std::string name, GameObject* object);
    void RemoveFromScene(GameObject* object);
	


    std::map<std::string, GameObject*> m_pGameObjects;

	ResourceManager* GetResourceManager() { return m_pResources; }
    Game* GetGame() { return m_pGame; }
   
};

#endif //__Scene_H__
