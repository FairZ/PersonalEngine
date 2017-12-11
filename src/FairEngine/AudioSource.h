#ifndef _AUDIOSOURCE_H_
#define _AUDIOSOURCE_H_
#include "Component.h"
#include "AL/al.h"
#include <string>

class Sound;
class Transform;

/// \brief Stores an openAL source and can play or stop its assigned sound
class AudioSource : public Component
{
public:
	void SetSound(std::string _soundName);
	void SetPitch(float _pitch);
	void SetGain(float _gain);
	void SetLooping(bool _looping);
	void Play();
	void Stop();
private:
	std::weak_ptr<Sound> m_sound;

	ALuint m_source;

	std::weak_ptr<Transform> m_transform;

	void Awake();
	void Update();
	void Destroy();
	void SetReferences();
	void Start();

};

#endif