#ifndef __Game_H__
#define __Game_H__

class ShaderProgram;
class AudioCue;

class Game : public GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;

    ResourceManager* m_pResources;

	Framework * m_pFramework;
    SceneManager* m_pSceneManager;

    Box2DWorld* m_pBox2DWorld;

    FBODefinition* m_pFBO;
    Mesh* m_pMesh;

    int PlayerHits;
	int m_PlayerScore;

    bool m_TestMode;

    PlayerController m_Controllers[4];

	AudioCue * m_pAudioCue;

	SoundPlayer* m_pSoundPlayer;
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	int m_HighScore;

	bool m_IsSoundOn;
	 bool m_Diffculty;


	 bool m_UserInterface;
	 bool m_RedBossKilled;
	 bool m_BlueBossKilled;

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void QueueEvent(Event* pEvent);
    virtual void ProcessEvents();
    virtual void OnEvent(Event* pEvent);

    virtual void Update(float deltatime);
    virtual void Draw();

    unsigned int GetWindowWidth() { return m_WindowWidth; }
    unsigned int GetWindowHeight() { return m_WindowHeight; }
	void SetWindowWidth(int width) {  m_WindowWidth = width; }
	void SetWindowHeight(int height) {  m_WindowHeight = height; }

    std::queue<Event*> m_EventQueue;
	
	SceneManager* GetSceneManager() { return m_pSceneManager; }

    Box2DWorld* GetWorld() { return m_pBox2DWorld; }

    PlayerController* GetController(int index) { return &m_Controllers[index]; }


	//json methods
	void LoadSceneFile(const char* filename);

    void SetTestMode(bool testmode) { m_TestMode = testmode; }
    bool GetTestMode() { return m_TestMode; }


	void SaveJson(cJSON * jroot, const char * saveFileName);
	void SaveSound(const char * saveFileName);

    void SetScore(int score) {  m_HighScore = score; }
    int GetScore() { return m_HighScore; }

	int GetPlayerScore() { return m_PlayerScore; }
	void SetPlayerScore(int playerscore) { m_PlayerScore = playerscore; }
    
    int GetPlayerHits() { return PlayerHits; }
    void AddPlayerHits() { PlayerHits++; }
    void SetPlayerHits(int playerhits) {PlayerHits = playerhits;}


	bool GetUserInterface() {return m_UserInterface; }
	void SetUserInterface(bool userinterface) { m_UserInterface = userinterface; }
	
	bool GetRedBossKilled() {return m_RedBossKilled; }
	void SetRedbosskilled(bool redbosskilled) { m_RedBossKilled = redbosskilled; }
	
	bool GetBlueBossKilled() {return m_BlueBossKilled; }
	void SetBlueBossKilled(bool bluebosskilled) { m_BlueBossKilled = bluebosskilled; }

	bool GetDiffculty() { return m_Diffculty; }
	void SetDiffculty(bool diffculty) { m_Diffculty = diffculty; }


	SoundPlayer* GetSoundPlayer() { return m_pSoundPlayer; }
	AudioCue * GetSoundCue() {	return m_pAudioCue;	}
	bool GetIsSoundOn() { return m_IsSoundOn; }

	void SetIsSoundOn(bool issoundon) { m_IsSoundOn = issoundon; }
	ResourceManager* GetResourceManager() { return m_pResources; }
};

#endif //__Game_H__
