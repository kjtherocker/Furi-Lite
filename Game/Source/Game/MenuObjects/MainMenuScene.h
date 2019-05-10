

class Game;
class Scene;

class MainMenuScene : public Scene
{
protected:

    vec3 m_Button1;
    vec3 m_Button2;
    vec3 m_Button3;
    vec3 m_Button4;

    SoundPlayer* m_pSoundPlayer;
    Tween* m_pTween;
	bool m_Tween;
	bool m_Up;
	float m_TimePassed;
	float m_Goal;
	int m_CurrentButton;

public:
	MainMenuScene(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~MainMenuScene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

