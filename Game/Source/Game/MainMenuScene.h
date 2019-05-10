

class Game;

class MainMenuScene : public Scene
{
protected:

    SoundPlayer* m_pSoundPlayer;

    int m_CurrentButton;

    vec3 m_Button1;
    vec3 m_Button2;
    vec3 m_Button3;
    vec3 m_Button4;

public:
	MainMenuScene(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~MainMenuScene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

