
#ifndef __SkyBoxObject_H__
#define __SkyBoxObject_H__

class GameObject;

class SkyBoxObject : public GameObject
{
protected:
    
public:
    SkyBoxObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    SkyBoxObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
	virtual ~SkyBoxObject();

	virtual void Update(float deltatime);

    void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);
};

#endif __SkyBoxObject_H__
