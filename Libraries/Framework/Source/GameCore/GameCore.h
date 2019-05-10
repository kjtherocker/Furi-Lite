#ifndef __GameCore_H__
#define __GameCore_H__

class Framework;

class GameCore
{
protected:
    Framework* m_pFramework;

public:
    GameCore(Framework* pFramework);
    virtual ~GameCore();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) = 0;
    virtual void LoadContent() = 0;

    virtual void Update(float deltatime) = 0;
    virtual void Draw() = 0;

    virtual void QueueEvent(Event* pEvent) = 0;

    Framework* GetFramework() { return m_pFramework; }
};

#endif //__GameCore_H__