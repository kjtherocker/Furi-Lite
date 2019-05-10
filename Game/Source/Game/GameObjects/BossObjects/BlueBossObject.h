
class GameObject;
class ProjectileObject;
class MagicCircleObject;
class PlayerObject;
#include <time.h>


class BlueBossObject : public BossObject
{
protected:
	float m_TestTimer;
	float m_MagicCircleTimer;
	float m_ProjectileTimer;
	float m_LazerTimer;
	float m_AttackTimer;
	int m_LazerCount;
	int m_ProCount;
	int m_Count;
	int m_ProjectileFinish;
	int m_ParticlesToAdd;

	float m_StateProjectileTimer;
	bool m_SwitchPrismatic;
	bool m_MagicCircleCreated;

	//New Vars
	bool m_AttackDone;
	bool m_Setup;
	int m_Attack;
	int m_Movement;
	int m_Node;
	float m_TeleportTimer;
	float m_TeleRand;


	float randomvalue;

	vec3 m_TeleportNode1;
	vec3 m_TeleportNode2;
	vec3 m_TeleportNode3;
	vec3 m_TeleportNode4;
	vec3 m_TeleportNode5;
	vec3 m_TeleportNode6;
	vec3 m_TeleportNode7;
	vec3 m_TeleportNode8;
	vec3 m_TeleportNode9;

	typedef void(BlueBossObject::*BossState1)(float delta);

	BossState1 m_BossState = 0;

	SimplePool<GameObject*> m_ParticlePool;
	SimplePool<GameObject*> m_ProjectilePool;
	SimplePool<GameObject*> m_MagicCirclePool;
	SimplePool<GameObject*> m_LazerPool;

	PlayerObject* m_PlayerObject;

	ParticleType m_pParticleType;
	ProjectileType m_ProjectileType;

public:
	BlueBossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
	BlueBossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
	virtual ~BlueBossObject();

	virtual void Update(float deltatime);

	void AddProjectileToPool();
	void AddProjectileToScene(PlayerObject * playerobject, ProjectileType type);

	void AddParticleToPool();
	void AddParticleToScene(ParticleType type);

	void AddMagicCircleToScene(PlayerObject * playerobject);
	void AddMagicCircleToPool();

	void AddLazerToScene(PlayerObject * playerobject);
	void AddLazerToPool();

	virtual void ProjectileAttack(float delta);
	virtual void GroundAttack(float delta);
	virtual void Teleport(float delta);
	virtual void Orbit(float delta);
	virtual void LazerAttack(float delta);

	void Reset();
	void SetTeleportPosition(int node);

	virtual void Clear(float delta);

	int GetHealth() { return m_Health; }
	virtual void ChangeHealth(int health);

	void SetPlayerObject(PlayerObject* playerobject);

	void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos, vec3 pos);

	BlueBossObject::BossState1 GetBossState();
};

