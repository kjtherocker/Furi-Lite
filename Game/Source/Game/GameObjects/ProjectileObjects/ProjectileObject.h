class GameObject;

enum ProjectileType
{
    NullTypes,
    Homing,
    Line,
};

class ProjectileObject : public GameObject
{
protected:
	SimplePool<GameObject*>* m_pPool;
    bool m_IsShot;
    vec3 m_Playerpos;
	b2Vec2 m_DirectionVector;
	Material* m_pMaterial;
    PlayerObject * m_pPlayerObject;
    ProjectileType m_ProjectileType;
	float m_Speed;
	float m_ProjectileLifetme;
	float m_TextureTimer;
	float AngleX = 0.0f;
	float AngleY = 0.0f;
	int m_Phase;

public:
    ProjectileObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
	ProjectileObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~ProjectileObject();

    virtual void Update(float deltatime);

    void Reset();

	void Destroy();

	void SetPool(SimplePool<GameObject*>* pPool) { m_pPool = pPool; }

    void RemoveFromScene();

    void SetScene(Scene * a_scene) { m_pScene = a_scene; }
    void SetType(ProjectileType type) { m_ProjectileType = type; }

    float GetSpeed() { return m_Speed; }
    void SetSpeed(float speed) { m_Speed = speed; }

	void SetLineMaterial(Material* material) { m_pMaterial = material; }

    void ResetTimers();

    void SetPlayer(PlayerObject* a_Playerobj);
    void SetPlayerPosition(vec3 pos);
    void FacePlayer();

};

