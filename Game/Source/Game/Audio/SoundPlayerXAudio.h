//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __SoundPlayerXAudio_H__
#define __SoundPlayerXAudio_H__

#include "WaveLoader.h"

#include <xaudio2.h>

class MyFileObject;
struct SoundObject;
class SoundChannel;
class VoiceCallback;
class SoundPlayer;

struct IXAudio2;
struct IXAudio2SourceVoice;
struct IXAudio2MasteringVoice;


struct SoundObject
{
protected:
    const char* m_pFileBuffer;
    MyWaveDescriptor m_WaveDesc; // Contains pointer to data buffer loaded from file
    XAUDIO2_BUFFER m_XAudioBuffer;

public:
    SoundObject();
    ~SoundObject();

    void Init(const char* pFileBuffer, MyWaveDescriptor waveDescriptor);

    XAUDIO2_BUFFER* GetXAudioBuffer() { return &m_XAudioBuffer; }
    bool IsValid() { return m_WaveDesc.valid; }
};

class SoundChannel
{
public:
    enum SoundChannelStates
    {
        SoundChannelState_Free,
        SoundChannelState_Playing,
        SoundChannelState_Paused,
    };

protected:
    IXAudio2SourceVoice* m_pSourceVoice;
    VoiceCallback* m_pVoiceCallback;

    SoundChannelStates m_CurrentState;
    double m_TimePlaybackStarted;

public:
    SoundChannel(IXAudio2* pEngine);
    ~SoundChannel();

    void PlaySound(SoundObject* pSoundObject);
    void StopSound();

    IXAudio2SourceVoice* GetSourceVoice() { return m_pSourceVoice; }
    void SetSourceVoice(IXAudio2SourceVoice* voice, VoiceCallback* pVoiceCallback) { m_pSourceVoice = voice; m_pVoiceCallback = pVoiceCallback; }

    SoundChannelStates GetState() { return m_CurrentState; }
    void SetState(SoundChannelStates state) { m_CurrentState = state; }

    double GetTimePlaybackStarted() { return m_TimePlaybackStarted; }
};

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
    SoundChannel* m_pChannel;

    VoiceCallback(SoundChannel* pChannel)
    {
        m_pChannel = pChannel;
    }

    virtual ~VoiceCallback() {}

    // Called when the voice has just finished playing a contiguous audio stream.
    void __stdcall OnStreamEnd()
    {
        m_pChannel->SetState( SoundChannel::SoundChannelState_Free );
    }

    // Unused methods are stubs.
    void __stdcall OnVoiceProcessingPassEnd() {}
    void __stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired) {}
    void __stdcall OnBufferEnd(void* pBufferContext) {}
    void __stdcall OnBufferStart(void* pBufferContext) {}
    void __stdcall OnLoopEnd(void* pBufferContext) {}
    void __stdcall OnVoiceError(void* pBufferContext, HRESULT Error) {}
};

class SoundPlayer
{
protected:
    static const int MAX_CHANNELS = 10;

    IXAudio2* m_pEngine;
    IXAudio2MasteringVoice* m_pMasteringVoice;
    IXAudio2SourceVoice* m_pSourceVoice;
    SoundChannel* m_pChannel;

public:
    SoundPlayer();
    ~SoundPlayer();

    SoundObject* LoadSound(const char* fullpath);

    int PlaySound(SoundObject* pSoundObject);
    void StopSound(int channelIndex);
};

#endif //__SoundPlayerXAudio_H__
