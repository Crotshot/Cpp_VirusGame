#include "pch.h"
#include "hp.h"
#include "methods.h"

Healthbar::Healthbar() {}

Healthbar::Healthbar(Healthbar& healthbar, sf::Color color, int width, int height) {
	this->GenerateHealthbar(color,width,height);
}

void Healthbar::GenerateHealthbar(sf::Color color, int width, int height) {
	originalWidth = width;
	originalHeight = height;
	bar.setSize(sf::Vector2f(width, height));
	bar.setFillColor(color);
	bar.setOrigin(width / 2, height / 2);	//Needs Unique originate
	shown = true;
}

void Healthbar::Update(sf::Vector2f position, float currentHealth, float maxHealth) {
	if (shown) {
		bar.setPosition(position);
		bar.setSize(sf::Vector2f(originalWidth * (currentHealth/maxHealth), originalHeight));//(currentHealth / maxHealth, 1);
	}
	else {
		bar.scale(0,0);
	}
}

void Healthbar::ToggleBar() {
	if (shown) {
		shown = false;
	}
	else {
		shown = true;
	}
}

sf::RectangleShape Healthbar::GetBar() {
	return bar;
}