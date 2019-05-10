
class GameObject;
class HealthBarObject;

class BossObject : public GameObject
{
protected:
	
    HealthBarObject* m_pHealthbar;
public:
    BossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    BossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~BossObject();

    virtual void Update(float deltatime);

	vec3 CalculateOffset(float radians, float radius);


	virtual void Start(float delta);

};

