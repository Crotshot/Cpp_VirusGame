#include "pch.h"
#include "barbedWire.h"
#include "textureHolder.h"
#include "methods.h"
#include <SFML/Audio.hpp>

BarbedWire::BarbedWire(){}

BarbedWire::BarbedWire(BarbedWire &barbedWire) {
	this->placed = TextureHolder::GetTexture("Assets/Graphics/Barbed_Wire.png");
	this->invalidSpot = TextureHolder::GetTexture("Assets/Graphics/Barbed_Wire_NotPlacable.png");
	this->validSpot = TextureHolder::GetTexture("Assets/Graphics/Barbed_Wire_Placable.png");
	this->state = State::INACTIVE;
}

BarbedWire::~BarbedWire() {}

void BarbedWire::GenerateBarbedWire(float health) {
	maxHealth = health;
	barbedSprite.setTexture(placed);
	OriginateCenter(barbedSprite);
	barbedSprite.setPosition(-1000, -1000);
	healthbar = new Healthbar(*healthbar, sf::Color::Blue, 20, 3);
}

float BarbedWire::GetHealth() {
	return health;
}

void BarbedWire::Damage(float Damage) {
	health -= Damage;
	if (health <= 0) {
		state = State::INACTIVE;
		SetPosition(sf::Vector2f(-1000, -1000));
	}
}

void BarbedWire::SetPosition(sf::Vector2f position) {
	barbedSprite.setPosition(position.x,position.y);
}

sf::Vector2f BarbedWire::GetPosition() {
	return barbedSprite.getPosition();
}

sf::Sprite BarbedWire::GetSprite() {
	return barbedSprite;
}

void BarbedWire::Update() {
	healthbar->Update(barbedSprite.getPosition(), health, maxHealth);
}

//Temporarily strange for testing
void BarbedWire::Placement(sf::Vector2f mousePos, bool _valid) {
	//Follow mouse cursor and turn green or red depending on valid placment points
	state = State::PLACING;
	barbedSprite.setPosition(mousePos);
	if (_valid) {
		barbedSprite.setTexture(validSpot);
		valid = true;
	}
	else {
		valid = false;
		barbedSprite.setTexture(invalidSpot);
	}
}
bool BarbedWire::Active() {
	if (state == State::ACTIVE) {
		return true;
	}
	else {
		return false;
	}
}

bool BarbedWire::Placing() {
	if (state == State::PLACING) {
		return true;
	}
	else {
		return false;
	}
}

void BarbedWire::Place(sf::Vector2f mousePos) {
	//Place barbed wire if it is in a valid spot
	if (valid) {
		state = State::ACTIVE;
		health = maxHealth;
		barbedSprite.setTexture(placed);
		barbedSprite.setPosition(mousePos);
	}
}

sf::RectangleShape BarbedWire::GetHealthbar() {
	return healthbar->GetBar();
}

bool BarbedWire::isValid() {
	return valid;
}

void BarbedWire::CancelPlacement() {
	state = State::INACTIVE;
	barbedSprite.setPosition(-1000, -1000);
}