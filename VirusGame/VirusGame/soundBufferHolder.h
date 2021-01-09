#pragma once

#ifndef soundBufferHolder_hpp
#define soundBufferHolder_hpp
#include <SFML/Audio.hpp>
#include <map>

using namespace sf;

class SoundBufferHolder {
public:
	SoundBufferHolder();
	static SoundBuffer& GetSound(std::string const& filename);//Retrieve Sound for given filename

private:
	std::map<std::string, SoundBuffer>m_Sound;
	static SoundBufferHolder* m_s_Instance;
};
#endif