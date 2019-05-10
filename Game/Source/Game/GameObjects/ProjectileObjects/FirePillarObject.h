
class GameObject;

class FirePillarObject : public GameObject
{
protected:

public:
    FirePillarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    FirePillarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~FirePillarObject();

    virtual void Update(float deltatime);

    void SetScene(Scene* a_scene) { m_pScene = a_scene; }

    void Reset();
	

};

