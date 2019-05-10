

class Game;
class Scene;

class ScoreMenu : public Scene
{
protected:
	int CurrentSelection;
	int m_Differencescore;
    bool m_WireFrameToggle;
    SoundPlayer* m_pSoundPlayer;
    SkyBoxObject * m_pSkyBoxObject;
public:
	ScoreMenu(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~ScoreMenu();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

