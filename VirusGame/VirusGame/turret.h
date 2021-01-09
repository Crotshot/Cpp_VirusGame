#ifndef Turret_hpp
#define Turret_hpp
#include <SFML/Graphics.hpp>
#include "infected.h"
#include <SFML/Audio.hpp>
#include "hp.h"

class Turret
{
private:
	sf::SoundBuffer gunBuffer;
	sf::Sound gunShot;
	float health, maxHealth, firerate, firerateTimer;
	sf::Texture placed, invalidSpot, validSpot, gunna, gunShot1, gunShot2, range;//Range Sprite replace gun sprite while placing
	sf::Sprite baseSprite, gunSprite;
	enum class State { ACTIVE, INACTIVE, PLACING };
	bool valid, hasTarget;
	Infected* target;
	Healthbar* healthbar;

public:
	Turret();
	Turret(Turret &turret);

	void Update(float time);	//Rotate and shoot closest target
	void GenerateTurret(float health);
	
	State state;
	
	sf::Vector2f GetPosition();

	void Damage(float Damage);
	~Turret();

	bool Active();					//Turret is shootable			
	bool Placing();	//Turret is being placed
	sf::Sprite GetBaseSprite();					
	sf::Sprite GetGunSprite();
	void Placement(sf::Vector2f mousePos, bool valid);
	void Place(sf::Vector2f mousePos);

	bool HasTarget();
	void Target(Infected* target);

	sf::RectangleShape GetHealthbar();

	float damageTimer;
	void Regen(float deltaTime);
	bool isValid();

	void CancelPlacement();
};
#endif

/*
Turrets shoot at the closest zombie until it is killed and then
retarget to another zombie in it range
*/