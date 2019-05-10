

class Game;
class Scene;
class SampleScene;
class MainMenuScene;
class ResourceManager;

class SceneManager 
{
protected:
	int MouseX;
	int MouseY;
	vec4 truepos;
	vector<Scene*> m_ActiveScenes;
    std::map<std::string, Scene*> m_pSceneObject;
public:
	SceneManager();
    virtual ~SceneManager();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

	void OnEvent(Event* pEvent);

    virtual void Update(float deltatime);
    virtual void Draw();

    void AddScene(const char* name, Scene* pScene) { m_pSceneObject[name] = pScene; }
    void PushScene(std::string name);
    void PopScene();

    Scene* GetScene(const char* name) { return m_pSceneObject[name]; }
    Scene* GetScene(std::string name) { return m_pSceneObject[name]; }

};


