#pragma once
#ifndef textureHolder_hpp
#define textureHolder_hpp
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class TextureHolder {
public:
	TextureHolder();
	static Texture& GetTexture(std::string const& filename);//Retrieve Texture for given filename

private:
	std::map<std::string, Texture>m_Textures;
	static TextureHolder* m_s_Instance;
};
#endif