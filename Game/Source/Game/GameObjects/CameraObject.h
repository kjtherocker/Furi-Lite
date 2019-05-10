#ifndef __CameraObject_H__
#define __CameraObject_H__

class PlayerObject;

class CameraObject : public GameObject
{
protected:
	mat4 m_MatView;
	mat4 m_MatProj;
    PlayerObject * m_pPlayerObject;
public:
    CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~CameraObject();

    virtual void Update(float deltatime);

    void SetPlayerObject(PlayerObject* playerobject) { m_pPlayerObject = playerobject; }

	mat4* GetViewMatrix() { return &m_MatView; }
	mat4* GetProjMatrix() { return &m_MatProj; }

	vec4 GetTrueMouseCoord(vec2 mousecoord);
};

#endif //__CameraObject_H__
