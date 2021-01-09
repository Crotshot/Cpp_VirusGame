#include "methods.h"
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <vector>

float Distance(sf::Vector2f point1, sf::Vector2f point2) {

	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

bool SquareCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
	float l1, l2, r1, r2, t1, t2, b1, b2;
	l1 = sprite1.getPosition().x - sprite1.getTexture()->getSize().x / 2;
	r1 = sprite1.getPosition().x + sprite1.getTexture()->getSize().x / 2;
	t1 = sprite1.getPosition().y - sprite1.getTexture()->getSize().y / 2;
	b1 = sprite1.getPosition().y + sprite1.getTexture()->getSize().y / 2;

	l2 = sprite2.getPosition().x - sprite2.getTexture()->getSize().x / 2; //   1    2    3    4
	r2 = sprite2.getPosition().x + sprite2.getTexture()->getSize().x / 2; // (l,t)(l,b)(r,t)(r,b)
	t2 = sprite2.getPosition().y - sprite2.getTexture()->getSize().y / 2;
	b2 = sprite2.getPosition().y + sprite2.getTexture()->getSize().y / 2;

	if (l1 <= l2 && r1 >= l2 && t1 <= t2 && b1 >= t2) {
		return true;
	}
	else if (l1 <= l2 && r1 >= l2 && t1 <= b2 && b1 >= b2) {
		return true;
	}
	else if (l1 <= r2 && r1 >= r2 && t1 <= t2 && b1 >= t2) {
		return true;
	}
	else if (l1 <= r2 && r1 >= r2 && t1 <= b2 && b1 >= b2) {
		return true;
	}

	if (l2 <= l1 && r2 >= l1 && t2 <= t1 && b2 >= t1) {
		return true;
	}
	else if (l2 <= l1 && r2 >= l1 && t2 <= b1 && b2 >= b1) {
		return true;
	}
	else if (l2 <= r1 && r2 >= r1 && t2 <= t1 && b2 >= t1) {
		return true;
	}
	else if (l2 <= r1 && r2 >= r1 && t2 <= b1 && b2 >= b1) {
		return true;
	}

	else {
		return false;
	}
}

bool CircularCollision(sf::Sprite sprite, sf::Vector2f center, float distance) {
	float l, r, t, b;
	l = sprite.getPosition().x - sprite.getTexture()->getSize().x / 2;
	r = sprite.getPosition().x + sprite.getTexture()->getSize().x / 2;
	t = sprite.getPosition().y - sprite.getTexture()->getSize().y / 2;
	b = sprite.getPosition().y + sprite.getTexture()->getSize().y / 2;

	if (Distance(center, sf::Vector2f(l,t)) <= distance) {
		return true;
	}
	else if (Distance(center, sf::Vector2f(l, b)) <= distance) {
		return true;
	}
	else if (Distance(center, sf::Vector2f(r, t)) <= distance) {
		return true;
	}
	else if (Distance(center, sf::Vector2f(r, b)) <= distance) {
		return true;
	}
	else {
		return false;
	}
}

void OriginateCenter(sf::Sprite &sprite) {
	sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5));
}