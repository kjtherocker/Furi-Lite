#include "GamePCH.h"

BossObject::BossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
		m_HasPhysics = false;
}

BossObject::BossObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{
	m_HasPhysics = false;
}

BossObject::~BossObject()
{

}

void BossObject::Update(float deltatime)
{
   

	
}

vec3 BossObject::CalculateOffset(float radians, float radius)
{
	vec3 offset = vec3(cosf(radians), 0, sinf(radians)) * radius;
	return offset;
}




void BossObject::Start(float delta)
{
     m_Position = vec3(vec3(5, 0, 0));
}

