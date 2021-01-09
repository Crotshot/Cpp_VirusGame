#ifndef infectecd_hpp
#define infectecd_hpp
#include <SFML/Graphics.hpp>
#include "core.h"
#include "hp.h"
//#include <SFML/Audio.hpp>

class Infected
{
private:
	//sf::Sound death;
	float health, maxHealth, speed, maxSpeed;
	sf::Texture infectedTexture, corpseTexture;
	sf::Sprite infectedSprite;
	enum class State { ALIVE, DEAD, NOTSPAWNED };
	Healthbar* healthbar;

public:
	Infected();
	Infected(Infected &infected);
	~Infected();

	State state;
	bool canMove;

	void Update(float time, Core& core);
	void GenerateInfected(/*sf::SoundBuffer infBuffer*/);
	void GenerateInfectedSpawn();
	float GetHealth();
	void Damage(float damage);
	sf::Vector2f GetPosition();
	void Spawn(sf::Vector2f hole);
	void Contact(int touching);

	bool Alive();
	bool Dead();

	sf::Sprite GetSprite();
	sf::RectangleShape GetHealthbar();
};
#endif

/*
The infected spawn on active spawners and walk toward the core
They spawn with randomized health and speed.
Upon Collision with a buuilding such as the turret or core they will cease movement and damage said building
If touching barbed wire they will be slowed and damaged

When an infected dies it becomes dead until it is spawned again
*/