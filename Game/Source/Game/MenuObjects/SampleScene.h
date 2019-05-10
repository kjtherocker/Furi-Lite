#ifndef __SampleScene_H__
#define __SampleScene_H__

class Game;
class Scene;
class SkyBoxObject;

class SampleScene : public Scene
{
protected:
	int MouseX;
	int MouseY;
	vec4 truepos;
    SkyBoxObject * m_pSkyBoxObject;
    Mesh* m_pMesh;
	int m_NumberOfLights;
	vec3 m_LightPos[5];
	vec3 m_LightColor[5];
    bool m_TestMode;
	bool m_WireFrameToggle;
   
public:
    SampleScene(Game* pGame, ResourceManager* pResources, Framework * pframework);
    virtual ~SampleScene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

	void OnEvent(Event* pEvent);

    virtual void Update(float deltatime);
    virtual void Draw();
};

#endif //__Scene_H__
