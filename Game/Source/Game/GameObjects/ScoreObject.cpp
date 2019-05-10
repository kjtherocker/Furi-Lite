#include "GamePCH.h"

ScoreObject::ScoreObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game)
	: GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial, game)
{
    m_Score = 0;
    mat4 world;
    for (int i = 0; i < 6; i++)
	{
		m_ScoreDigitMeshes[i] = pMesh;
		m_ScoreDigitPositions[i] = pos;
		m_ScoreDigitPositions[i].x = pos.x - (i * 1.5f);
	}
}

ScoreObject::ScoreObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game * game)
	: GameObject(pScene, name, pos, rot, scale, meshname, materialname, game)
{

	m_Score = 0;
	mat4 world;
	for (int i = 0; i < 6; i++)
	{
		m_ScoreDigitMeshes[i] = m_pGame->GetResourceManager()->GetMesh(meshname);
		m_ScoreDigitPositions[i] = pos;
		m_ScoreDigitPositions[i].x = pos.x - (i * 1.4f);
	}
}

ScoreObject::~ScoreObject()
{
}

void ScoreObject::Update(float deltatime)
{
    if (m_Score > 999999)
    {
      this->SetScore(999999);
    }
    if (m_Score < 0)
    {
        m_Score = 0;
    }

//    float(m_Score) += deltatime;

    int subtractedValue = 0;
    m_ScoreDigitValues[0] = m_Score % 10;
    subtractedValue += m_ScoreDigitValues[0];
    m_ScoreDigitValues[1] = ((m_Score % 100) - subtractedValue) / 10;
    subtractedValue += (m_ScoreDigitValues[1] * 10);
    m_ScoreDigitValues[2] = ((m_Score % 1000) - subtractedValue) / 100;
    subtractedValue += (m_ScoreDigitValues[2] * 100);
    m_ScoreDigitValues[3] = ((m_Score % 10000) - subtractedValue) / 1000;
    subtractedValue += (m_ScoreDigitValues[3] * 1000);
    m_ScoreDigitValues[4] = ((m_Score % 100000) - subtractedValue) / 10000;
    subtractedValue += (m_ScoreDigitValues[4] * 10000);
    m_ScoreDigitValues[5] = ((m_Score % 1000000) - subtractedValue) / 100000;
    subtractedValue += (m_ScoreDigitValues[5] * 100000);

}

void ScoreObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
    for (int i = 0; i < 6; i++)
    {
        if (m_pMesh == 0)
        {
            return;
        }

        ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

        mat4 world;
        world.SetIdentity();
        world.CreateSRT(m_Scale, m_Rotation,float( m_ScoreDigitValues[i]));

        
        world.SetIdentity();
        world.CreateSRT(m_Scale, m_Rotation, m_ScoreDigitPositions[i]);

        m_ScoreDigitMeshes[i]->SetupAttributes(pShaderProgram);
		
        m_ScoreDigitMeshes[i]->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos, m_ScoreDigitValues[i]);

        m_ScoreDigitMeshes[i]->Draw(pShaderProgram);

    }
}

void ScoreObject::SetScore(int score)
{
	m_Score = score;
}

void ScoreObject::AddScore(int a_Score)
{
    m_Score += a_Score;
}

void ScoreObject::MinusScore(int a_score)
{
    m_Score -= a_score;
}


void ScoreObject::SetScoreToZero()
{
	m_Score = 0;
}

void ScoreObject::Reset()
{
    SetScoreToZero();
}
