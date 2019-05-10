class GameObject;


class LazerObject : public GameObject
{
protected:
	SimplePool<GameObject*>* m_pPool;
    bool m_IsShot;
	float m_LazerLifetme;

public:
    LazerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    LazerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~LazerObject();

    virtual void Update(float deltatime);

    void Reset();

	void Destroy();

	void SetPool(SimplePool<GameObject*>* pPool) { m_pPool = pPool; }

    void RemoveFromScene();

    void SetScene(Scene * a_scene) { m_pScene = a_scene; }

    void ResetTimers();

};

