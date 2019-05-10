

class Game;
class Scene;

class OptionMenuConfirm : public Scene
{
protected:
	int CurrentSelection;
    SoundPlayer* m_pSoundPlayer;
public:
	OptionMenuConfirm(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~OptionMenuConfirm();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();

	void OnEvent(Event* pEvent);
};

