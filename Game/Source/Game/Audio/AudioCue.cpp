#include "GamePCH.h"

AudioCue::AudioCue(Game * game)
{
	m_pGame = game;

   // InitializeSounds();
}

AudioCue::~AudioCue()
{
}

void AudioCue::InitializeSounds()
{
	Projectile = std::vector<SoundObject*>();

	Projectile.push_back(m_pGame->GetResourceManager()->GetSoundObj("Fire"));
	Projectile.push_back(m_pGame->GetResourceManager()->GetSoundObj("Fire2"));
}

SoundObject* AudioCue::GetSound(SoundType soundtype)
{
    if (soundtype == SoundType_Projectile)
    {
        // Pull a random footstep sound out of the vector and return it
        return Projectile.at(rand() % Projectile.size());
    }
    else
    {
        return nullptr;
    }
}