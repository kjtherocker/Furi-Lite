#ifndef __AudioWrapper_H__
#define __AudioWrapper_H__

class Game;
struct SoundObject;
using namespace std;

enum SoundType
{    
    Sound_Type_Null,
    SoundType_Projectile,
};

class AudioCue
{
protected:
    Game* m_pGame;

    SoundType m_SoundType;
    std::vector<SoundObject*> Projectile;

public:
	AudioCue(Game * game);
    ~AudioCue();

    void InitializeSounds();

	SoundObject* GetSound(SoundType soundtype);
};

#endif
