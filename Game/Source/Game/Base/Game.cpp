#include "GamePCH.h"

Game::Game(Framework* pFramework)
: GameCore( pFramework )
{
    m_pImGuiManager = 0;

    m_WindowWidth = -1;
    m_WindowHeight = -1;

	m_pFramework = pFramework;

	m_pSceneManager = 0;
    m_pResources = 0;
    m_pFBO = 0;
    m_pMesh = 0;
	m_Diffculty = 0;
}

Game::~Game()
{
    while( m_EventQueue.size() != 0 )
    {
        Event* pEvent = m_EventQueue.front();
        m_EventQueue.pop();
        delete pEvent;
    }

	delete m_pSceneManager;
    delete m_pBox2DWorld;
    delete m_pResources;
	delete m_pImGuiManager;
    delete m_pFBO;
    delete m_pMesh;
	delete m_pSoundPlayer;
	delete m_pAudioCue;
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    glViewport( 0, 0, width, height );

    m_WindowWidth = width;
    m_WindowHeight = height;
}

void Game::LoadContent()
{
    // Seed random.
    srand( (unsigned int)GetSystemTime() );

    CheckForGLErrors();

    // Turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // Turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_pFBO = new FBODefinition();
    m_pFBO->Create(1024, 1024, GL_NEAREST, GL_NEAREST, true, 32, true);

    m_pMesh = new Mesh();

	m_pSoundPlayer = new SoundPlayer();

    m_pResources = new ResourceManager();

    PlayerHits = 0;

	m_UserInterface = 0;
	m_RedBossKilled = 0;
	m_BlueBossKilled = 0;

    ShowCursor(false);

	srand(unsigned int(time(NULL)));

    // Load our shaders.
    {
        m_pResources->AddShader("Texture", new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag"));
        m_pResources->AddShader("Health", new ShaderProgram("Data/Shaders/Healthbar.vert", "Data/Shaders/Healthbar.frag"));
        m_pResources->AddShader("Lighting", new ShaderProgram("Data/Shaders/Lighting.vert", "Data/Shaders/Lighting.frag"));
        m_pResources->AddShader("Particle", new ShaderProgram("Data/Shaders/Particle.vert", "Data/Shaders/Particle.frag"));
        m_pResources->AddShader("TextureWithLighting", new ShaderProgram("Data/Shaders/TexAndLight.vert", "Data/Shaders/TexAndLight.frag"));
        m_pResources->AddShader("SkyBox", new ShaderProgram("Data/Shaders/SkyBox.vert", "Data/Shaders/SkyBox.frag"));
		m_pResources->AddShader("PostProcessing", new ShaderProgram("Data/Shaders/PostProcessing.vert", "Data/Shaders/PostProcessing.frag"));
        m_pResources->AddShader("SkyBoxReflection", new ShaderProgram("Data/Shaders/CubeMapReflection.vert", "Data/Shaders/CubeMapReflection.frag"));
		m_pResources->AddShader("Score", new ShaderProgram("Data/Shaders/score.vert", "Data/Shaders/score.frag"));
        CheckForGLErrors();
    }

    // Create meshes.
    {
        m_pResources->AddMesh("Box", Mesh::CreateBox(vec2(1, 1), false));
        m_pResources->AddMesh("Cube", Mesh::CreateCube(vec3(1, 1, 1)));
		m_pResources->AddMesh("Plane", Mesh::CreatePlane(vec2(0.0f, 0.0f), ivec2(200, 200), vec2(6.5f, 21.0f), vec2(1, 1)));
        m_pResources->AddMesh("InverseCube", Mesh::CreateInverseCube(vec3(1, 1, 1)));
        m_pResources->AddMesh("Obj", Mesh::CreateFromObj("Data/obj/cube.obj"));
        m_pResources->AddMesh("Sphere", Mesh::CreateFromObj("Data/obj/cic.obj"));
        m_pResources->AddMesh("Invertedcube", Mesh::CreateFromObj("Data/obj/InvertedCube.obj"));
		m_pResources->AddMesh("Slantedcube", Mesh::CreateFromObj("Data/obj/SlantedCube.obj"));
    }


    // Load our textures.
    {
      
        //Level Textures
        m_pResources->AddTexture("Megaman", LoadTexture("Data/Textures/Megaman.png"));
        m_pResources->AddTexture("MagicCircleRed", LoadTexture("Data/Textures/MagicCircleRed.png"));
        m_pResources->AddTexture("RedBoss", LoadTexture("Data/Textures/RedBoss.png"));
		m_pResources->AddTexture("RedBossWall", LoadTexture("Data/Textures/RedbossWall.png"));
		m_pResources->AddTexture("RedAreanaWall", LoadTexture("Data/Textures/RedArenaWall.png"));
		m_pResources->AddTexture("BlueFloor", LoadTexture("Data/Textures/BlueArenaFloor.png"));
		m_pResources->AddTexture("BlueAreanaWall", LoadTexture("Data/Textures/BlueArenaWall.png"));
		m_pResources->AddTexture("BlueBoss", LoadTexture("Data/Textures/BlueBoss.png"));
		m_pResources->AddTexture("BothBosses", LoadTexture("Data/Textures/BothBosses.png"));
        m_pResources->AddTexture("Crate", LoadTexture("Data/Textures/Crate.png"));
        m_pResources->AddTexture("Fire", LoadTexture("Data/Textures/Fire.png"));
        m_pResources->AddTexture("Target", LoadTexture("Data/Textures/target.png"));
		m_pResources->AddTexture("Numbers", LoadTexture("Data/Textures/Numbers.png"));
        m_pResources->AddTexture("ClearScore", LoadTexture("Data/Textures/ClearScore.png"));
        m_pResources->AddTexture("FireGround", LoadTexture("Data/Textures/FireGround.png"));
        m_pResources->AddTexture("Grey", LoadTexture("Data/Textures/SolidGrey.png"));

        //Particles
		m_pResources->AddTexture("RedParticle1", LoadTexture("Data/Textures/Particles/Red_Particle1.png"));
		m_pResources->AddTexture("RedParticle2", LoadTexture("Data/Textures/Particles/Red_Particle2.png"));
		m_pResources->AddTexture("RedParticle3", LoadTexture("Data/Textures/Particles/Red_Particle3.png"));
		m_pResources->AddTexture("RedParticle4", LoadTexture("Data/Textures/Particles/Red_Particle4.png"));
		m_pResources->AddTexture("RedParticle5", LoadTexture("Data/Textures/Particles/Red_Particle5.png"));

        //Menu items
        m_pResources->AddTexture("MainMenu", LoadTexture("Data/Textures/MainMenu.png"));
		m_pResources->AddTexture("CompleteMainMenu", LoadTexture("Data/Textures/Complete_Menu.png"));
		m_pResources->AddTexture("TitleMenu", LoadTexture("Data/Textures/Title_Menu.png"));
		m_pResources->AddTexture("OptionMenu", LoadTexture("Data/Textures/Option_Template.png"));
		m_pResources->AddTexture("YesMenu", LoadTexture("Data/Textures/YesMenu.png"));
		m_pResources->AddTexture("NoMenu", LoadTexture("Data/Textures/NoMenu.png"));
		m_pResources->AddTexture("OFF", LoadTexture("Data/Textures/OFF.png"));
		m_pResources->AddTexture("ON", LoadTexture("Data/Textures/ON.png"));
		m_pResources->AddTexture("Sound", LoadTexture("Data/Textures/Sound.png"));
		m_pResources->AddTexture("CrimsonKnightPrompt", LoadTexture("Data/Textures/CrimsonKnightPrompt.png"));
		m_pResources->AddTexture("AzureKnightPrompt", LoadTexture("Data/Textures/AzureKnightPrompt.png"));
		m_pResources->AddTexture("BothPrompt", LoadTexture("Data/Textures/BothPrompt.png"));
		m_pResources->AddTexture("OptionsPrompt", LoadTexture("Data/Textures/OptionsPrompt.png"));
		m_pResources->AddTexture("DiffcultyNormal", LoadTexture("Data/Textures/DiffcultyNormal.png"));
		m_pResources->AddTexture("DiffcultyEasy", LoadTexture("Data/Textures/DiffcultyEasy.png"));
		m_pResources->AddTexture("Confirm", LoadTexture("Data/Textures/Confirm.png"));
        m_pResources->AddTexture("ScoreMenu", LoadTexture("Data/Textures/ScoreMenu.png"));
        
        //Projectiles
		m_pResources->AddTexture("RedProjectile", LoadTexture("Data/Textures/Projectiles/Projectile.png"));
        m_pResources->AddTexture("BlueProjectile", LoadTexture("Data/Textures/Projectiles/Azure_Projectile.png"));
		m_pResources->AddTexture("HomingProjectile1", LoadTexture("Data/Textures/Projectiles/HomingProjectile1.png"));
		m_pResources->AddTexture("HomingProjectile2", LoadTexture("Data/Textures/Projectiles/HomingProjectile2.png"));
		m_pResources->AddTexture("HomingProjectile3", LoadTexture("Data/Textures/Projectiles/HomingProjectile3.png"));
		m_pResources->AddTexture("HomingProjectile4", LoadTexture("Data/Textures/Projectiles/HomingProjectile4.png"));
		m_pResources->AddTexture("HomingProjectile5", LoadTexture("Data/Textures/Projectiles/HomingProjectile5.png"));
        m_pResources->AddTexture("Lazer", LoadTexture("Data/Textures/Projectiles/Lazer.png"));


        //Others
        m_pResources->AddTexture("Invisible", LoadTexture("Data/Textures/Invisible.png"));

        m_pResources->AddTexture("Arrow", LoadTexture("Data/Textures/Arrow.png"));
        m_pResources->AddTexture("FBO", m_pFBO->GetColorTextureHandle());
        CheckForGLErrors();

        const char* filenames[6]{ "Data/Textures/SkyBox.png", "Data/Textures/SkyBox.png" , "Data/Textures/SkyBox.png" 
            , "Data/Textures/SkyBox.png", "Data/Textures/SkyBox.png", "Data/Textures/SkyMegaman.png" };


        m_pResources->AddTexture("CubeMap", LoadTextureCubemap(filenames));
        CheckForGLErrors();
    }

    //Creat our Sounds
    {
        m_pResources->AddSoundPlayer("SoundPlayer", new SoundPlayer());
        m_pResources->AddSoundObject("MagicCircleSound", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/MagicCircle.wav"));
        m_pResources->AddSoundObject("MagicCircle2", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/MagicCircle2.wav"));
        m_pResources->AddSoundObject("Fire", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/Fire.wav"));
        m_pResources->AddSoundObject("Fire2", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/Fire2.wav"));
        m_pResources->AddSoundObject("ProjectileShot", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/Shoot.wav"));
        m_pResources->AddSoundObject("PickUp", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/PickUp.wav"));
        m_pResources->AddSoundObject("Teleport", m_pResources->GetSoundPlayer("SoundPlayer")->LoadSound("Data/AudioFiles/Teleport.wav"));
    }

    // Create our materials.
    {
		


        
        m_pResources->AddMaterial("TextureInvisible", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Invisible")));
		m_pResources->AddMaterial("ScoreNumbers", new Material(m_pResources->GetShader("Score"), m_pResources->GetTexture("Numbers")));
        m_pResources->AddMaterial("TextureMegaman", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Megaman")));
        m_pResources->AddMaterial("TextureTarget", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Target")));
        m_pResources->AddMaterial("TextureRedBoss", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("RedBoss")));
		m_pResources->AddMaterial("TextureRedBossWall", new Material(m_pResources->GetShader("PostProcessing"), m_pResources->GetTexture("RedBossWall")));
		m_pResources->AddMaterial("TextureRedAreanaWall", new Material(m_pResources->GetShader("TextureWithLighting"), m_pResources->GetTexture("RedAreanaWall")));
		m_pResources->AddMaterial("TextureBlueArenaWall", new Material(m_pResources->GetShader("TextureWithLighting"), m_pResources->GetTexture("BlueAreanaWall")));
		m_pResources->AddMaterial("TextureBlueAreanaFloor", new Material(m_pResources->GetShader("TextureWithLighting"), m_pResources->GetTexture("BlueFloor")));
		m_pResources->AddMaterial("TextureBlueBoss", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BlueBoss")));
		m_pResources->AddMaterial("TextureBothBosses", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BothBosses")));
        m_pResources->AddMaterial("TextureFireGround", new Material(m_pResources->GetShader("TextureWithLighting"), m_pResources->GetTexture("FireGround")));
        m_pResources->AddMaterial("TextureGrey", new Material(m_pResources->GetShader("TextureWithLighting"), m_pResources->GetTexture("Grey")));

		m_pResources->AddMaterial("TextureSkyBoxReflection", new Material(m_pResources->GetShader("SkyBoxReflection"), m_pResources->GetTexture("CubeMap")));

        
        m_pResources->AddMaterial("TextureClearScore", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("ClearScore")));
        m_pResources->AddMaterial("TextureProjectile", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("RedProjectile")));
        m_pResources->AddMaterial("TextureProjectileBlue", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BlueProjectile")));
        m_pResources->AddMaterial("TextureMagicCircleRed", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("MagicCircleRed")));
        m_pResources->AddMaterial("TextureFirePilar", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Fire")));
        m_pResources->AddMaterial("TextureCrate", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Crate")));
		m_pResources->AddMaterial("TextureHomingProjectile1", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HomingProjectile1")));
		m_pResources->AddMaterial("TextureHomingProjectile2", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HomingProjectile2")));
		m_pResources->AddMaterial("TextureHomingProjectile3", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HomingProjectile3")));
		m_pResources->AddMaterial("TextureHomingProjectile4", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HomingProjectile4")));
		m_pResources->AddMaterial("TextureHomingProjectile5", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HomingProjectile5")));
        m_pResources->AddMaterial("TextureLazer", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Lazer")));

        m_pResources->AddMaterial("TextureSkyBox", new Material(m_pResources->GetShader("SkyBox"), m_pResources->GetTexture("CubeMap")));


		m_pResources->AddMaterial("TextureRedParticle1", new Material(m_pResources->GetShader("Particle"), m_pResources->GetTexture("RedParticle1")));
		m_pResources->AddMaterial("TextureRedParticle2", new Material(m_pResources->GetShader("Particle"), m_pResources->GetTexture("RedParticle2")));
		m_pResources->AddMaterial("TextureRedParticle3", new Material(m_pResources->GetShader("Particle"), m_pResources->GetTexture("RedParticle3")));
		m_pResources->AddMaterial("TextureRedParticle4", new Material(m_pResources->GetShader("Particle"), m_pResources->GetTexture("RedParticle4")));
		m_pResources->AddMaterial("TextureRedParticle5", new Material(m_pResources->GetShader("Particle"), m_pResources->GetTexture("RedParticle5")));

		m_pResources->AddMaterial("TextureMainMenuComplete", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("CompleteMainMenu")));
		m_pResources->AddMaterial("TextureScoreMenu", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("ScoreMenu")));
		m_pResources->AddMaterial("TextureConfirm", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Confirm")));
        m_pResources->AddMaterial("TextureMainMenu", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("MainMenu")));
		m_pResources->AddMaterial("TextureTitleMenu", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TitleMenu")));
		m_pResources->AddMaterial("TextureOptionMenu", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionMenu")));
		m_pResources->AddMaterial("TextureYesMenu", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("YesMenu")));
		m_pResources->AddMaterial("TextureNoMenu", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("NoMenu")));
		m_pResources->AddMaterial("TextureOFF", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OFF")));
		m_pResources->AddMaterial("TextureON", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("ON")));
		m_pResources->AddMaterial("TextureNormal", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("DiffcultyNormal")));
		m_pResources->AddMaterial("TextureEasy", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("DiffcultyEasy")));

		m_pResources->AddMaterial("TextureSound", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Sound")));
		m_pResources->AddMaterial("TextureCrimsonKnightPrompt", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("CrimsonKnightPrompt")));
		m_pResources->AddMaterial("TextureAzureKnightPrompt", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("AzureKnightPrompt")));
		m_pResources->AddMaterial("TextureBothPrompt", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BothPrompt")));
		m_pResources->AddMaterial("TextureOptionsPrompt", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionsPrompt")));

        
        

		m_pResources->AddMaterial("PostProcessedMegaman", new Material(m_pResources->GetShader("PostProcessing"), m_pResources->GetTexture("OptionMenu")));

        m_pResources->AddMaterial("ParticleRedBoss", new Material(m_pResources->GetShader("Particle"), m_pResources->GetTexture("RedBoss")));
        m_pResources->AddMaterial("HealthMegaman", new Material(m_pResources->GetShader("Health"), m_pResources->GetTexture("Megaman")));
        m_pResources->AddMaterial("LightingMegaman", new Material(m_pResources->GetShader("TextureWithLighting"), m_pResources->GetTexture("Megaman")));
        m_pResources->AddMaterial("TextureArrow", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Arrow")));
        m_pResources->AddMaterial("FBOTexture", new Material(m_pResources->GetShader("PostProcessing"), m_pResources->GetTexture("FBO")));
    }
    
    m_pBox2DWorld = new Box2DWorld(0, 0);

	m_pSceneManager = new SceneManager();
	m_pSceneManager->LoadContent();

	m_pAudioCue = new AudioCue(this);
	m_pAudioCue->InitializeSounds();
	m_IsSoundOn = false;
	m_HighScore = 0;
	m_PlayerScore = 0;
	m_TestMode = false;

    LoadSceneFile("Data/Json/test.scene");

    m_pSceneManager->AddScene("SampleScene", new SampleScene(this, m_pResources, m_pFramework));
    m_pSceneManager->AddScene("MainMenu", new MainMenuScene(this, m_pResources, m_pFramework));
	m_pSceneManager->AddScene("TitleMenu", new TitleMenu(this, m_pResources, m_pFramework));
	m_pSceneManager->AddScene("OptionMenu", new OptionMenu(this, m_pResources, m_pFramework));
	m_pSceneManager->AddScene("DiffcultyConfirm", new DiffcultyConfirm(this, m_pResources, m_pFramework));
	m_pSceneManager->AddScene("OptionMenuConfirm", new OptionMenuConfirm(this, m_pResources, m_pFramework));
    m_pSceneManager->AddScene("BlueBoss", new BlueBossScene(this, m_pResources, m_pFramework));
    m_pSceneManager->AddScene("ScoreMenu", new ScoreMenu(this, m_pResources, m_pFramework));
	m_pSceneManager->AddScene("BothBoss", new BothBoss(this, m_pResources, m_pFramework));

	m_pSceneManager->SetRenderScene(m_pSceneManager->GetScene("SampleScene"));

    m_pSceneManager->PushScene("TitleMenu");
    

    m_pSceneManager->LoadContent();

    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();



    CheckForGLErrors();
}

void Game::QueueEvent(Event* pEvent)
{
    m_EventQueue.push( pEvent );
}

void Game::ProcessEvents()
{
    while( m_EventQueue.size() != 0 )
    {
        Event* pEvent = m_EventQueue.front();
        m_EventQueue.pop();

        OnEvent( pEvent );
        delete pEvent;
    }
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent( pEvent );

	m_pSceneManager->OnEvent( pEvent );

    m_Controllers[0].OnEvent( pEvent );
}

void Game::Update(float deltatime)
{
    // Process events at the start of the frame before updating anything else in the game.
    ProcessEvents();
    m_pBox2DWorld->Update(deltatime);
    // Once our events are processes, tell imgui we're starting a new frame.
	if (m_TestMode)
	{
		m_pImGuiManager->StartFrame((float)m_WindowWidth, (float)m_WindowHeight, deltatime);
	}
	

	m_pSceneManager->Update( deltatime );


}

void Game::Draw()
{
    m_pFBO->Bind();

    // Clear the screen to dark blue.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport(0, 0, 1024, 1024);
    // Draw the scene
    if (m_pSceneManager->GetRenderScene() != nullptr)
    {
        m_pSceneManager->GetRenderScene()->Draw();
    }

    m_pFBO->Unbind();

    glClearColor(0.25f, 0.5f, 0.25f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 1024, 1024);


    m_pResources->GetMaterial("FBOTexture")->SetTexture(m_pFBO->GetColorTextureHandle());

    if (m_pSceneManager->GetRenderScene() != nullptr)
    {
        m_pSceneManager->GetRenderScene()->Draw();
    }

    CheckForGLErrors();

    // Tell imgui we're at the end of our frame, so it will draw all queued objects.
   

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0, m_WindowWidth, m_WindowHeight);
    m_pSceneManager->Draw();

	if (m_TestMode)
	{
		m_pImGuiManager->EndFrame();
	}

    CheckForGLErrors();
}

void Game::LoadSceneFile(const char * filename)
{
	const char* filecontents = LoadCompleteFile(filename, 0);

	cJSON* jRoot = cJSON_Parse(filecontents);

	cJSON* jGameObjectsArray = cJSON_GetObjectItemCaseSensitive(jRoot, "GameObjects");

	cJSON* jGameObject = cJSON_GetArrayItem(jGameObjectsArray, 0);


	cJSON* jSound = cJSON_GetObjectItem(jGameObject, "Sound");

	cJSON* jScore = cJSON_GetObjectItem(jGameObject, "HighScore");


	cJSON* jUser = cJSON_GetObjectItem(jGameObject, "UserInterface");

	cJSON* jRedboss = cJSON_GetObjectItem(jGameObject, "RedBoss");

	cJSON* jBlueboss = cJSON_GetObjectItem(jGameObject, "BlueBoss");


	m_UserInterface = bool(jUser->valueint);

	m_RedBossKilled = bool(jRedboss->valueint);
	
	m_BlueBossKilled = bool(jBlueboss->valueint);

	m_IsSoundOn = bool(jSound->valueint);

	m_HighScore = jScore->valueint;



	cJSON_Delete(jRoot);

	delete[] filecontents;
}

void Game::SaveJson(cJSON * jroot, const char * saveFileName)
{

	char* jsonstring = cJSON_Print(jroot);

	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, saveFileName, "wb");
	if (filehandle)
	{
		fwrite(jsonstring, 1, strlen(jsonstring), filehandle);
		fclose(filehandle);
	}
	free(jsonstring);
}

void Game::SaveSound(const char * saveFileName)
{

	cJSON* jRoot = cJSON_CreateObject();

	cJSON* jArray = cJSON_CreateArray();
	cJSON_AddItemToObject(jRoot, "GameObjects", jArray);

	cJSON* jItem = cJSON_CreateObject();
	cJSON_AddItemToArray(jArray, jItem);

	cJSON_AddNumberToObject(jItem, "HighScore", m_HighScore);

	cJSON_AddNumberToObject(jItem, "UserInterface", m_UserInterface);

	cJSON_AddNumberToObject(jItem, "RedBoss", m_RedBossKilled);

	cJSON_AddNumberToObject(jItem, "BlueBoss", m_BlueBossKilled);

	cJSON_AddNumberToObject(jItem, "Sound", m_IsSoundOn);

	SaveJson(jRoot, saveFileName);

	cJSON_Delete(jRoot);
}
