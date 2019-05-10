

class Game;
class Scene;

class OptionMenu : public Scene
{
protected:
	int CurrentSelection;
	bool SoundSetting;
	bool ClearScoreSetting;
	bool m_Tween;
	bool m_Up;
    SoundPlayer* m_pSoundPlayer;
	vec3 m_Button1;
	vec3 m_Button2;
	vec3 m_Button3;
	Tween* m_pTween;
	float m_TimePassed;
	float m_Goal;
public:
    OptionMenu(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~OptionMenu();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

