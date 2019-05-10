#include "GamePCH.h"

#if _DEBUG
#pragma comment( lib, "../Output/Framework/Win32/Debug/Framework.lib" )
#pragma comment( lib, "../Output/Box2D/Win32/Debug/Box2D.lib" )
#else
#pragma comment( lib, "../Output/Framework/Win32/Release/Framework.lib" )
#pragma comment( lib, "../Output/Box2D/Win32/Release/Box2D.lib" )
#endif

#pragma comment( lib, "../Output/Framework/Win32/Debug/Framework.lib" )

#pragma comment( lib, "XAudio2.lib" )
#pragma comment( lib, "opengl32.lib" )

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if _DEBUG
	MyMemory_ForgetAllPreviousAllocations();
#endif

    Framework* pFramework = new Framework();

    GameCore* pGame = new Game( pFramework );

    pFramework->Init( SCREEN_WIDTH, SCREEN_HEIGHT );
    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete( pGame );
    delete( pFramework );

#if _DEBUG
	MyMemory_ValidateAllocations( true );
#endif
}
