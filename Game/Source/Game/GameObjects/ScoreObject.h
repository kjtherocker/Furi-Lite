#pragma once
class Game;
class Mesh;
class Scene;


class ScoreObject : public GameObject
{
public:
	ScoreObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
	ScoreObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
	virtual ~ScoreObject();

	void Update(float deltatime);
	void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);
    int GetScore() { return m_Score;  }
	void SetScore(int score);
    void AddScore(int a_Score);
    void MinusScore(int a_score);
	void SetScoreToZero();
    void AddToScore(int score) { m_Score += score; }

    void Reset();
protected:
	Mesh* m_ScoreDigitMeshes[6];
	int m_ScoreDigitValues[6];
	vec3 m_ScoreDigitPositions[6];
	
    int m_Score;


};
