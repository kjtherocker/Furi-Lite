#ifndef __PlayerObject_H__
#define __PlayerObject_H__

enum PlayerState
{
	PlayerState_Normal,
	PlayerState_Teleporting,
	PlayerState_Shooting,
	PlayerState_Cutscene,
};

enum PlayerMovement
{
    PlayerMovement_Standing,
    PlayerMovement_Moving


};

class Tween;
class HealthBarObject;
class ScoreObject;

class PlayerObject : public GameObject
{
protected:
	PlayerState m_PlayerState;
	PlayerController* m_pController;
	HealthBarObject * m_pHealthbar;
    PlayerMovement  m_PlayerMovment;
    ScoreObject * m_pScoreobject;

    Tween* m_pTween;

	float m_TeleportTimer;
	float m_FireTimer;
	float m_InvincibleTimeLeft;
	float m_debugtimer;
	float m_Teleportrange;
	float m_Speed;
    int m_Hits;

	bool m_DebugInvincibility;
    bool m_IsShooting;
    bool m_IsCollidingWithWall;
    bool m_Invincibility;
	vec3 m_PreviousPosition;
	vec3 m_CursorPosition;
	
public:
	PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
	PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
	virtual ~PlayerObject();

	void SetController(PlayerController* pController);

	virtual void Update(float deltatime);

	virtual void BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal);

	bool GetIsShooting();

    void Reset();

    void SetScore(ScoreObject* score) { m_pScoreobject = score; }

	void SetIsShooting(bool isshooting);
	void SendCursorPosition(vec3 pos);

	PlayerState GetPlayerState() { return m_PlayerState; }

	void SetPlayerState(PlayerState playerstate) { m_PlayerState = playerstate; }

};

#endif //__PlayerObject_H__
