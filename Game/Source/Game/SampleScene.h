#ifndef __SampleScene_H__
#define __SampleScene_H__

class Game;


class SampleScene : public Scene
{
protected:
	int MouseX;
	int MouseY;
	vec4 truepos;
   
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
