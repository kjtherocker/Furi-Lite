
class GameObject;
class SoundPlayer;
class FirePillarObject;

class MagicCircleObject : public GameObject
{
protected:
    float m_MagicCircleObjectLifetme;
    float m_AttackTimer;
    float m_PilarRotation;
    bool m_IsAttacking;
	SimplePool<GameObject*>* m_pPool;
    FirePillarObject* m_pFirePillar;
    b2FixtureDef fixturedef;
 
    bool m_PillarDeath;
public:
	MagicCircleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
	MagicCircleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~MagicCircleObject();

    virtual void Update(float deltatime);
    virtual void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);

    void SetScene(Scene* a_scene) { m_pScene = a_scene; }

    void ResetTimers();

    void Reset();

    void RemoveFromScene();
	
	bool GetIsAttacking() { return m_IsAttacking; }

	void Destroy();

	void SetPool(SimplePool<GameObject*>* pPool) { m_pPool = pPool; }
};

