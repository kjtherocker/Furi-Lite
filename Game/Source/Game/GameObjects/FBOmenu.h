
class GameObject;
class ResourceManager;


class FBOmenu : public GameObject
{
protected:
	float m_LifeTime;
	ResourceManager* m_pResource;
    
public:
    FBOmenu(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    FBOmenu(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~FBOmenu();

    virtual void Update(float deltatime);
	virtual void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);

	void SetScene(Scene * a_scene) { m_pScene = a_scene; }
	void RemoveFromScene();

    void Reset();

    void SetLifeTime(float lifetime) { m_LifeTime = lifetime;}

	void Destroy();
};

