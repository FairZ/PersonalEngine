#include "Sound.h"
#include "vorbis/vorbisfile.h"
#include <iostream>

Sound::Sound(std::string _name, std::string _filePath)
{
	m_name = _name;
	std::vector<char> data;
	ALenum format;
	ALenum frequency;

	//load the given file
	LoadOgg(_filePath,data,format,frequency);
	//generate buffer for the sound
	alGenBuffers(1, &m_bufferIndex);
	//push the data to openAL
	alBufferData(m_bufferIndex,format,&data[0],static_cast<ALsizei>(data.size()),frequency);
}

Sound::~Sound()
{
	alDeleteBuffers(1, &m_bufferIndex);
}

ALuint Sound::GetBufferIndex()
{
	return m_bufferIndex;
}

//NOTE: this function is not my own but i do not know its original source so cannot correctly reference it
void Sound::LoadOgg(std::string _path, std::vector<char> &_bufferData, ALenum &_format, ALsizei &_freq)
{
  int endian = 0;
  int bitStream = 0;
  long bytes = 0;
  char array[2048] = { 0 };
  vorbis_info *pInfo = NULL;
  OggVorbis_File oggFile = { 0 };

  // Use the inbuilt fopen to create a file descriptor
  if (ov_fopen(_path.c_str(), &oggFile) != 0)
  {
    throw std::exception();
  }

  // Extract information from the file header
  pInfo = ov_info(&oggFile, -1);

  // Record the format required by OpenAL
  if (pInfo->channels == 1)
  {
    _format = AL_FORMAT_MONO16;
  }
  else
  {
    _format = AL_FORMAT_STEREO16;
  }

  // Record the sample rate required by OpenAL
  _freq = pInfo->rate;

  // Keep reading bytes from the file to populate the output buffer
  while (true)
  {
    // Read bytes into temporary array
    bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

    if (bytes < 0)
    {
      ov_clear(&oggFile);
      std::cout << "Failed to decode file '" << _path << "'." << std::endl;
      throw std::exception();
    }
    else if (bytes == 0)
    {
      break;
    }

    // Copy from temporary array into output buffer
    _bufferData.insert(_bufferData.end(), array, array + bytes);
  }

  // Clean up and close the file
  ov_clear(&oggFile);
}