

class Game;
class Scene;

class DiffcultyConfirm : public Scene
{
protected:
	int CurrentSelection;
    SoundPlayer* m_pSoundPlayer;
public:
	DiffcultyConfirm(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~DiffcultyConfirm();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

