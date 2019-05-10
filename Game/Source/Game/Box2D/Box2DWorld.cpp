#include "GamePCH.h"

Box2DWorld::Box2DWorld(mat4* pMatView, mat4* pMatProj)
{
    m_pWorld = 0;

    m_pContactListener = 0;

    m_pGround = 0;

    m_UnusedTime = 0;

    CreateWorld( pMatView, pMatProj );
}

Box2DWorld::~Box2DWorld()
{
    Cleanup();
}

void Box2DWorld::CreateWorld(mat4* pMatView, mat4* pMatProj)
{
    m_pWorld = new b2World( b2Vec2(0.0f, 0.0f ) );

    // Setup contact listener object.
    {
        m_pContactListener = new Box2DContactListener();

        m_pWorld->SetContactListener( m_pContactListener );
    }

    // Create a static ground body at 0,0
    {
        b2BodyDef bodydef;
        bodydef.position = b2Vec2( 0, 0 );
        bodydef.type = b2_staticBody;
        m_pGround = m_pWorld->CreateBody( &bodydef );
    }
}

void Box2DWorld::Update(float deltatime)
{
    if( false )
    {
        m_pWorld->Step( 1/60.0f, 8, 2 );
    }
    else
    {
        m_UnusedTime += deltatime;

        float timestep = 1/60.0f;

        while( m_UnusedTime > timestep )
        {
            m_pWorld->Step( timestep, 8, 2 );
            m_UnusedTime -= timestep;
        }

        m_pWorld->ClearForces();
    }
}

void Box2DWorld::Cleanup()
{
    delete m_pWorld;
    delete m_pContactListener;

    m_pGround = 0;
}
