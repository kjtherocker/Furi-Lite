#ifndef __GameObject_H__
#define __GameObject_H__

class ShaderProgram;
class Mesh;
class Scene;
class Game;

enum PhysicsCategories
{
    PhysicsCategory_Default = 0x0001,
    PhysicsCategory_Wall = 0x0002,
    PhysicsCategory_Attack = 0x0004,
    PhysicsCategory_NoCollision = 0x0008,
    PhysicsCategory_Player = 0x0010
   // PhysicsCategory_ = 0x0020,
   

};

using namespace std;

class GameObject
{
protected:
    vec3 m_InitialPosition;
    vec3 m_InitialRotation;

    Scene* m_pScene;

    unsigned int m_RenderOrder;

	bool m_HasPhysics;

    std::string m_Name;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;
	vec3 m_BossPos;

    int m_Health;
    int m_MaxHealth;

    b2Filter m_Filter;

    PhysicsCategories m_Category;
    PhysicsCategories m_Mask;

    b2Body* m_pPhysicsBody;

	Game* m_pGame;

    OurDebugDraw* m_pDebugDraw;
    Mesh* m_pMesh;
    Material* m_pMaterial;

protected:
    b2Fixture* AddPhysicsShape(b2Shape* shape, bool dynamic, bool active, float density, bool sensor);

public:
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
    virtual ~GameObject();

    unsigned int GetRenderOrder() { return m_RenderOrder; }
    void SetRenderOrder(unsigned int order) { m_RenderOrder = order; }

    virtual void Init(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);

    virtual void Reset();
    virtual void AddToScene(Scene* pScene);
    virtual void RemoveFromScene();

    virtual void Update(float deltatime);
    virtual void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);

    virtual void BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal);
    virtual void EndContact(b2Fixture* pOtherFixture);

    b2Fixture* AddPhysicsBox(vec2 size, bool dynamic, bool active, float density, bool sensor = false);
    b2Fixture* AddPhysicsDentedBox(vec2 size, float indent, bool dynamic, bool active, float density, bool sensor = false);
    b2Fixture* AddPhysicsChain(b2Vec2* pointlist, int numpoints, bool dynamic, bool active, float density, bool sensor = false);
    b2Fixture* AddPhysicsCircle(float radius, bool dynamic, bool active, float density, bool sensor = false);

	void AddJoint(float posX, float posY, b2Body* body1, b2Body* body2, bool HasMotor, float32 motorspeed, float32 maxmotortorque, bool HasLimit, float32 lowerlimit, float32 higherlimit);
	void AddPrismaticJoint(float posX, float posY,b2Vec2 direction, b2Body* body1, b2Body* body2, bool HasLimit , int lowertran, int highertran);

    // Getters/Setters
    void SetName(std::string name) { m_Name = name; }
    void SetMesh(Mesh* pMesh) { m_pMesh = pMesh; }
    void SetMaterial(Material* pMaterial) { m_pMaterial = pMaterial; }

	void SetHealth(int health);
    void SetMaxHealth(int maxhealth) { m_MaxHealth = maxhealth; }
    void ModifyHealth(int health);

	void SetBossPos(vec3 pos);
	
	virtual void SetHasPhysics(bool sethasphysics) { m_HasPhysics = sethasphysics; }
    std::string GetName() { return m_Name; }
    Mesh* GetMesh() { return m_pMesh; }
    Material* GetMaterial() { return m_pMaterial; }
    b2Body* GetPhysicsBody() { return m_pPhysicsBody; }

    void SetScene(Scene* pScene) { m_pScene = pScene; }

    virtual void SetInitialPosition(vec3 pos) { m_InitialPosition = pos; }
    virtual void SetInitialRotation(vec3 rot) { m_InitialRotation = rot; }

    virtual void SetPosition(vec3 pos);
    virtual void SetRotation(vec3 rot);
    virtual void SetScale(vec3 scale) { m_Scale = scale; }

    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale()  { return m_Scale; }
};

#endif //__GameObject_H__
