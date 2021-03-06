#ifndef _SOUND_H_
#define _SOUND_H_
#include "Resource.h"
#include "AL/al.h"
#include <vector>

/// \brief Resource to handle the loading and storage of sounds
class Sound : public Resource
{
public:
	/// \private
	Sound(std::string _name, std::string _filePath);
	/// \private
	~Sound();

	ALuint GetBufferIndex();
private:
	ALuint m_bufferIndex;

	void LoadOgg(std::string _path, std::vector<char> &_bufferData, ALenum &_format, ALsizei &_freq);
};


#endif