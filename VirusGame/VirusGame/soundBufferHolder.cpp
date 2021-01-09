#include "pch.h"
#include "soundBufferHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

SoundBufferHolder* SoundBufferHolder::m_s_Instance = nullptr;

SoundBufferHolder::SoundBufferHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::SoundBuffer& SoundBufferHolder::GetSound(std::string const& filename) {
	auto& m = m_s_Instance->m_Sound;

	auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		auto& sound = m[filename];

		sound.loadFromFile(filename);

		return sound;
	}
}