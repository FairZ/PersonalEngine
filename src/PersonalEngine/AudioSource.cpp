#include "AudioSource.h"
#include "Sound.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Entity.h"

void AudioSource::SetSound(std::string _soundName)
{
	m_sound = m_resourceManager.lock()->GetSound(_soundName);
	alSourcei(m_source,AL_BUFFER,m_sound.lock()->GetBufferIndex());
}

void AudioSource::SetPitch(float _pitch)
{
	alSourcef(m_source,AL_PITCH,_pitch);
}

void AudioSource::SetGain(float _gain)
{
	alSourcef(m_source,AL_GAIN,_gain);
}

void AudioSource::SetLooping(bool _looping)
{
	if (_looping)
		alSourcei(m_source,AL_LOOPING, AL_TRUE);
	else
		alSourcei(m_source,AL_LOOPING, AL_FALSE);
}

void AudioSource::Play()
{
	if(!m_sound.expired())
	{
		alSourcePlay(m_source);
	}
}

void AudioSource::Stop()
{
	if(!m_sound.expired())
	{
		alSourceStop(m_source);
	}
}

void AudioSource::Awake()
{
	alGenSources(1,&m_source);
	alSourcef(m_source,AL_PITCH,1.0f);
	alSourcef(m_source,AL_GAIN,1.0f);
	alSourcei(m_source,AL_LOOPING, AL_FALSE);
}

void AudioSource::Update()
{
	glm::vec3 pos = m_transform.lock()->GetPosition();
	alSource3f(m_source,AL_POSITION,pos.x, pos.y, pos.z);
}

void AudioSource::Start()
{
	SetReferences();
}

void AudioSource::SetReferences()
{
	m_transform = m_entity->m_transform;
}

void AudioSource::Destroy()
{
	alDeleteSources(1, &m_source);
}