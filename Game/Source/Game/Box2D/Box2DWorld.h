#ifndef __Box2DWorld_H__
#define __Box2DWorld_H__

class Box2DWorld;
class MaterialDefinition;

class Box2DWorld
{
protected:
    b2World* m_pWorld;
    Box2DContactListener* m_pContactListener;

    b2Body* m_pGround;

    float m_UnusedTime;

public:
    Box2DWorld(mat4* pMatView, mat4* pMatProj);
    ~Box2DWorld();

    void CreateWorld(mat4* pMatView, mat4* pMatProj);
    void Update(float deltatime);
    void Cleanup();

    b2World* GetWorld() { return m_pWorld; }

    b2Body* GetGroundBody() { return m_pGround; }
};

#endif //__Box2DWorld_H__
