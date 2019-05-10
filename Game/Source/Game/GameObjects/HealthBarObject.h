
#ifndef __HealthBarObject_H__
#define __HealthBarObject_H__

class GameObject;

class HealthBarObject : public GameObject
{
protected:
    


public:
    HealthBarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, Game* game);
    HealthBarObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname, Game* game);
	virtual ~HealthBarObject();

	virtual void Update(float deltatime);

    void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);

    void SetMaxHealth(int maxhealth);
    void SetHealth(int health);
    void DecreaseHealth(int health);


};

#endif __HealthBarObject_H__
