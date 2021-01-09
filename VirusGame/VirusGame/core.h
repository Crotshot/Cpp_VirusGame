#ifndef core_hpp
#define core_hpp
#include <SFML/Graphics.hpp>
#include <vector>
#include "hp.h"

class Core
{
private:
	float health, maxHealth;
	void Regen(float deltaTime);
	sf::Sprite coreSprite;
	Healthbar* healthbar;

public:
	Core();
	Core(Core &core);
	void GenerateNewCore(float health);

	void Update(float time);

	float GetHealth();
	void Damage(float damage);
	float damageTimer;
	sf::Vector2f GetPosition();
	void SetPosition(int x, int y);
	sf::Sprite GetSprite();
	~Core();

	sf::RectangleShape GetHealthbar();
};
#endif
/*
The core is the center piece that the infected want to destroy
Upon its destruction it is game over
*/