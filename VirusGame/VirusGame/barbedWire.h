#ifndef barbedWire_hpp
#define barbedWire_hpp
#include <SFML/Graphics.hpp>
#include <vector>
#include "hp.h"

class BarbedWire
{
private:
	float health, maxHealth;
	sf::Texture placed, invalidSpot, validSpot;
	sf::Sprite barbedSprite;
	enum class State { ACTIVE, INACTIVE, PLACING};
	bool valid;
	Healthbar* healthbar;

public:
	BarbedWire();
	BarbedWire(BarbedWire &barbedWire);
	~BarbedWire();

	void GenerateBarbedWire(float health);

	State state;
	float GetHealth();
	void Damage(float Damage);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);

	sf::Sprite GetSprite();

	bool Active();
	void Update();

	void Placement(sf::Vector2f mousePos, bool _valid);
	void Place(sf::Vector2f mousePos);
	bool Placing();

	sf::RectangleShape GetHealthbar();

	void CancelPlacement();
	bool isValid();
};
#endif
/*
Placed by player for money, slows and damages zombies.
Degrades when touched by zombies and eventually breaks.
*/