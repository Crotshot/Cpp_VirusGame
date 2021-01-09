#ifndef Healthbar_hpp
#define Healthbar_hpp
#include <SFML/Graphics.hpp>
#include <vector>

class Healthbar
{
private:
	sf::RectangleShape bar;
	bool shown;
	float originalWidth, originalHeight;

public:
	Healthbar();
	Healthbar(Healthbar& healthbar, sf::Color color, int width, int height);
	void GenerateHealthbar(sf::Color color, int width, int height);
	void Update(sf::Vector2f position, float currentHealth, float maxHealth);
	void ToggleBar();

	sf::RectangleShape GetBar();
};
#endif // !HP_hpp



/*
Hp bars for all entities that have health



-->Needs To
Size dynamically
Color change?
Originate
Use in all hp contained classes ez pz
*/