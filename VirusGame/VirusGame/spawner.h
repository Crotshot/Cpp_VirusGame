#ifndef Spawner_hpp
#define Spawner_hpp
#include <SFML/Graphics.hpp>

class Spawner
{
private:
	sf::Sprite spawnerSprite;
	enum class State { ACTIVE, INACTIVE};

public:
	Spawner();
	Spawner(Spawner &spawner);
	void GenerateSpawner();
	float lifetime;
	State spawnerState;

	sf::Vector2f GetPosition();

	void Return();
	~Spawner();

	bool Active();
	sf::Sprite GetSprite();
};
#endif

/*
Array of spawners 
Spawners will become active and be given a position
Zombies will come out of the spawners that are active
Spawners have a lifetime and will dissappear after a minute or so
When spawners life ends it will become incative and return off screen
*/