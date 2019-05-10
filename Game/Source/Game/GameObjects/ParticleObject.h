
class GameObject;
class ResourceManager;

enum ParticleType
{
    NullType,
    AnimatedParticle,
    ExplosiveParticle,
};

class ParticleObject : public GameObject
{
protected:
	float m_Lifetime;
	float m_Speed;
    bool m_Created;
	SimplePool<GameObject*>* m_pPool;
	b2Vec2 m_DirectionVector;
	ResourceManager* m_pResource;
    ParticleType m_ParticleType;
	int m_Phase;
    
public:
	ParticleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
	ParticleObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~ParticleObject();

    virtual void Update(float deltatime);
	virtual void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);

	void SetScene(Scene * a_scene) { m_pScene = a_scene; }
	void RemoveFromScene();

    void SetLifeTime(float lifetime) { m_Lifetime = lifetime;}

	void SetPool(SimplePool<GameObject*>* pPool) { m_pPool = pPool; }
    void SetParticleType(ParticleType type) { m_ParticleType = type; }

	void Destroy();
};

