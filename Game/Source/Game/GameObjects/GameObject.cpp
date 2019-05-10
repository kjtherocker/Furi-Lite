#include "GamePCH.h"

GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
{
    Init( pScene, name, pos, rot, scale, pMesh, pMaterial );
	m_pGame = game;
}

GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
{
    ResourceManager* pResources = pScene->GetResourceManager();
    Init( pScene, name, pos, rot, scale, pResources->GetMesh( meshname ), pResources->GetMaterial( materialname ) );
	m_pGame = game;
}

GameObject::~GameObject()
{
}

void GameObject::Init(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
{
    m_InitialPosition = pos;
    m_InitialRotation = rot;

    m_pScene = pScene;

    m_RenderOrder = 0;

    m_Name = name;

    m_Category = PhysicsCategory_Default;
    m_Mask = PhysicsCategory_Player;

    m_Mask;

    m_Position = pos;
    m_Rotation = rot;
    m_Scale = scale;

    m_pPhysicsBody = 0;

	m_HasPhysics = false;

    m_pMesh = pMesh;
    m_pMaterial = pMaterial;
}

void GameObject::Reset()
{
    m_Position = m_InitialPosition;
    m_Rotation = m_InitialRotation;

    if( m_pPhysicsBody )
    {
        m_pPhysicsBody->SetLinearVelocity( b2Vec2( 0, 0 ) );
        m_pPhysicsBody->SetAngularVelocity( 0 );
        m_pPhysicsBody->SetTransform( b2Vec2( m_InitialPosition.x, m_InitialPosition.y ), m_InitialRotation.z * PI / 180 );
        m_pPhysicsBody->SetAwake( true );
    }
}

void GameObject::AddToScene(Scene* pScene)
{
    m_pScene = pScene;
    m_pScene->AddToScene( m_Name, this );
}

void GameObject::RemoveFromScene()
{
    if( m_pScene )
    {
        m_pScene->RemoveFromScene( this );
        m_pScene = 0;
    }
}

void GameObject::Update(float deltatime)
{
	//.createSRT(1, m_Rotation, 0);

	if (m_pPhysicsBody)
	{

		if (m_pPhysicsBody)
		{
			if (m_HasPhysics == false)
			{
				m_pPhysicsBody->SetTransform(b2Vec2(m_Position.x, m_Position.y), -m_Rotation.z * PI / 180.0f);
			}
			else if (m_HasPhysics == true)
			{
				b2Vec2 pos = m_pPhysicsBody->GetPosition();
				float32 angle = -m_pPhysicsBody->GetAngle() / PI * 180.0f;

				m_Position.x = pos.x;
				m_Position.y = pos.y;
				m_Rotation.z = angle;
			}
		}
	}
}

void GameObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
    if( m_pMesh == 0 )
        return;

    ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

	mat4 world;
	world.CreateSRT( m_Scale, m_Rotation, m_Position );

    m_pMesh->SetupAttributes( pShaderProgram );
    m_pMesh->SetupUniforms( m_pMaterial, &world, pMatView, pMatProj, campos, m_BossPos);
    m_pMesh->Draw( pShaderProgram );

}

void GameObject::BeginContact(b2Fixture* pOtherFixture, vec2 worldPosition, vec2 worldNormal)
{
    OutputMessage( "Normal: %s, %0.2f, %0.2f\n", m_Name.c_str(), worldNormal.x, worldNormal.y );
}

void GameObject::EndContact(b2Fixture* pOtherFixture)
{
    //OutputMessage( "Normal: %s, %0.2f, %0.2f\n", m_Name.c_str(), worldNormal.x, worldNormal.y );
}

b2Fixture* GameObject::AddPhysicsShape(b2Shape* shape, bool dynamic, bool active, float density, bool sensor)
{
    if( m_pPhysicsBody == 0 )
    {
        b2BodyDef bodydef;
        bodydef.position.Set( m_Position.x, m_Position.y ); // bottom-left corner
        bodydef.angle = -m_Rotation.z * PI / 180.0f;
        if( dynamic )
            bodydef.type = b2_dynamicBody;
        else
            bodydef.type = b2_staticBody;

        bodydef.active = active;

        m_pPhysicsBody = m_pScene->GetBox2DWorld()->GetWorld()->CreateBody( &bodydef );
        m_pPhysicsBody->SetUserData( this );
    }

    b2FixtureDef fixturedef;
    fixturedef.shape = shape;
    fixturedef.density = density;
    fixturedef.isSensor = sensor;
    fixturedef.friction = 0.2f;
    fixturedef.restitution = 0;
    uint16 catA = fixturedef.filter.categoryBits = m_Category;
    uint16 maskA = fixturedef.filter.maskBits = m_Mask;

    return m_pPhysicsBody->CreateFixture( &fixturedef );
}

b2Fixture* GameObject::AddPhysicsBox(vec2 size, bool dynamic, bool active, float density, bool sensor)
{
    b2PolygonShape boxshape;
    boxshape.SetAsBox( size.x/2, size.y/2 );

    return AddPhysicsShape( &boxshape, dynamic, active, density, sensor );
}

b2Fixture* GameObject::AddPhysicsDentedBox(vec2 size, float indent, bool dynamic, bool active, float density, bool sensor)
{
    b2PolygonShape boxshape;

    b2Vec2 points[8];
    float hx = size.x/2;
    float hy = size.y/2;

    points[0].Set( -hx         , -hy + indent ); // lower left - left
    points[1].Set( -hx + indent, -hy          ); // lower left - lower
    points[2].Set(  hx - indent, -hy          ); // lower right - lower
    points[3].Set(  hx         , -hy + indent ); // lower right - right
    points[4].Set(  hx         ,  hy - indent ); // upper right - right
    points[5].Set(  hx - indent,  hy          ); // upper right - upper
    points[6].Set( -hx + indent,  hy          ); // upper left - upper
    points[7].Set( -hx         ,  hy - indent ); // upper left - left

    boxshape.Set( points, 8 );

    return AddPhysicsShape( &boxshape, dynamic, active, density, sensor );
}

b2Fixture* GameObject::AddPhysicsChain(b2Vec2* pointlist, int numpoints, bool dynamic, bool active, float density, bool sensor)
{
    b2ChainShape chainshape;
    chainshape.CreateChain( pointlist, numpoints );

    return AddPhysicsShape( &chainshape, dynamic, active, density, sensor );
}

b2Fixture* GameObject::AddPhysicsCircle(float radius, bool dynamic, bool active, float density, bool sensor)
{
    b2CircleShape circleshape;
    circleshape.m_radius = radius;

    return AddPhysicsShape( &circleshape, dynamic, active, density, sensor );
}

void GameObject::AddPrismaticJoint(float posX, float posY, b2Vec2 direction, b2Body * body1, b2Body * body2, bool HasLimit, int lowertran, int highertran)
{
	// Declare a joint definition object
	b2PrismaticJointDef jointdef;
	// Select a world space anchor point
	b2Vec2 anchorpos(posX, posY);
	// Initialize the joint definition with the 2 bodies and the world space anchor
	jointdef.Initialize(body1, body2, anchorpos, direction);
	// Create the actual joint in the world'


	if (HasLimit == true)
	{
		jointdef.enableLimit = true;
		jointdef.lowerTranslation = float32(lowertran);
		jointdef.upperTranslation = float32(highertran);
	}
	m_pScene->GetBox2DWorld()->GetWorld()->CreateJoint(&jointdef);
}

void GameObject::SetHealth(int health)
{
	m_Health = health;
}

void GameObject::ModifyHealth(int health)
{
    m_Health += health;
}

void GameObject::SetPosition(vec3 pos)
{
    m_Position = pos;
    if( m_pPhysicsBody )
        m_pPhysicsBody->SetTransform( b2Vec2( m_Position.x, m_Position.y ), -m_Rotation.z * PI / 180.0f );
}

void GameObject::SetRotation(vec3 rot)
{
    m_Rotation = rot;
    if( m_pPhysicsBody )
        m_pPhysicsBody->SetTransform( b2Vec2( m_Position.x, m_Position.y ), -m_Rotation.z * PI / 180.0f );
}
void GameObject::SetBossPos(vec3 pos)
{
	vec3 time = 0;
	m_BossPos = pos;

	if (m_BossPos.x  == 8)
	{
		bool holyfuck = true;
	}
}
