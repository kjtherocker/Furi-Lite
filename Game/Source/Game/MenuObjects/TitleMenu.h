

class Game;
class Scene;

class TitleMenu : public Scene
{
protected:

    SoundPlayer* m_pSoundPlayer;
public:
    TitleMenu(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~TitleMenu();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

