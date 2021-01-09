#ifndef Methods_hpp
#define Methods_hpp
#include <SFML/Graphics.hpp>
#include <vector>

	float Distance(sf::Vector2f pointA, sf::Vector2f pointB);
	bool SquareCollision(sf::Sprite sprite1, sf::Sprite sprite2);
	bool CircularCollision(sf::Sprite sprite, sf::Vector2f center, float distance);
	void OriginateCenter(sf::Sprite &sprite);

#endif

/*
A class with helper methods for maths calculations
and collision detection
*/