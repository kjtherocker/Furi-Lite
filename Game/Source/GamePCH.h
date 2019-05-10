#ifndef __GamePCH_H__
#define __GamePCH_H__

#include "../../Libraries/Framework/Source/FrameworkPCH.h"

#include <queue>



#include "Common/Memory/CPPList.h"
#include "Common/Memory/Memory.h"
#include "Common/SimplePool.h"

#include "Common/Main/ImGuiManager.h"

#include "Game/Mesh/VertexFormat.h"
#include "Game/Mesh/Material.h"
#include "Game/Mesh/Mesh.h"

#include "Game/Box2D/Box2DContactListener.h"
#include "Game/Box2D/Box2DWorld.h"

#include "Game/GameObjects/PlayerController.h"
#include "Game/GameObjects/GameObject.h"
#include "Game/GameObjects/CameraObject.h"
#include "Game/GameObjects/PlayerObject.h"
#include "Game\GameObjects\HealthBarObject.h"
#include "Game\GameObjects\ParticleObject.h"
#include "Game\GameObjects\SkyBoxObject.h"

#include "Game\GameObjects\ProjectileObjects\ProjectileObject.h"
#include "Game\GameObjects\ProjectileObjects\MagicCircleObject.h"
#include "Game\GameObjects\ProjectileObjects\FirePillarObject.h"
#include "Game\GameObjects\ProjectileObjects\LazerObject.h"

#include "Game\GameObjects\BossObjects\BossObject.h"
#include "Game\GameObjects\BossObjects\BlueBossObject.h"
#include "Game\GameObjects\BossObjects\RedBossObject.h"
#include "Game\GameObjects\ScoreObject.h"

#include "Game\Audio\SoundPlayerXAudio.h"
#include "Game\Audio\WaveLoader.h"
#include "Game\Audio\AudioCue.h"

#include "Game\Base\Tween.h"
#include "Game\Base\TweenFuncs.h"
#include "Game\Base\FBODefinition.h"
#include "Game/Base/ResourceManager.h"
#include "Game/Base/Scene.h"

#include "Game\MenuObjects\SceneManager.h"
#include "Game\MenuObjects\MainMenuScene.h"
#include "Game\MenuObjects\OptionsMenu.h"
#include "Game\MenuObjects\TitleMenu.h"
#include "Game\MenuObjects\SampleScene.h"
#include "Game\MenuObjects\OptionsMenuConfirm.h"
#include "Game\MenuObjects\DiffcultyConfirm.h"
#include "Game\MenuObjects\BlueBossScene.h"
#include "Game\MenuObjects\HUDScene.h"
#include "Game\MenuObjects\ScoreMenu.h"
#include "Game\GameObjects\FBOmenu.h"
#include "Game\MenuObjects\BothBoss.h"

#include "Game/Events/GameEvents.h"
#include "Game/Events/RemoveFromSceneEvent.h"

#include "Game\Box2D\RayCastResultCallback.h"

#include "Game\Constaints.h"




#include "Game/Base/Game.h"


#endif //__GamePCH_H__
