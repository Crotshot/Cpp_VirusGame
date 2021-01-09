#include "pch.h"
#include "turret.h"
#include "textureHolder.h"
#include "methods.h"

Turret::Turret() {}

Turret::Turret(Turret &turret) {
	this->placed = TextureHolder::GetTexture("Assets/Graphics/Turret_base.png");
	this->invalidSpot = TextureHolder::GetTexture("Assets/Graphics/Turret_base_NotPlacable.png");
	this->validSpot = TextureHolder::GetTexture("Assets/Graphics/Turret_base_Placable.png");
	this->gunna = TextureHolder::GetTexture("Assets/Graphics/Turret_Top.png");
	this->gunShot1 = TextureHolder::GetTexture("Assets/Graphics/Turret_Top_Shoot1.png");
	this->gunShot2 = TextureHolder::GetTexture("Assets/Graphics/Turret_Top_Shoot2.png");
	this->range = TextureHolder::GetTexture("Assets/Graphics/turretRange.png");
	this->gunBuffer.loadFromFile("Assets/Sounds/GunShot.wav");
	this->gunShot.setBuffer(gunBuffer);
	this->gunShot.setVolume(1.8);
	this->state = State::INACTIVE;
}

Turret::~Turret() {
	delete healthbar;
	healthbar = NULL;
	target = NULL; //Delete pointer but not the infected
}

void Turret::GenerateTurret(float health) {
	maxHealth = health;
	this->health = maxHealth;
	baseSprite.setTexture(placed);
	gunSprite.setTexture(gunna);

	OriginateCenter(gunSprite);
	OriginateCenter(baseSprite);

	baseSprite.setPosition(-1000, -1000);
	gunSprite.setPosition(-1000, -1000);

	healthbar = new Healthbar(*healthbar, sf::Color::Green, 50, 5);
	firerate = 0.33;//0.33 seconds per shot or ~180.6 RPM
	firerateTimer = 0;
	target = false;
}

void Turret::Update(float time) {
	if (state == State::ACTIVE && hasTarget) {
		if (target->GetHealth() > 0 && CircularCollision(target->GetSprite(), GetPosition(), 125)) {

			float angle = (atan2(target->GetPosition().y - gunSprite.getPosition().y,
				target->GetPosition().x - gunSprite.getPosition().x)
				* 180) / 3.141;

			gunSprite.setRotation(angle + 1.5708);

			if (firerateTimer < firerate) {
				firerateTimer += time;
				if (firerateTimer > 0.1) {
					gunSprite.setTexture(gunna);
				}
			}
			else {
				firerateTimer = 0;
				gunShot.setPitch(0.9 + static_cast <float> (rand() % 1)/3);
				gunShot.play();															//this does not play
				if ((rand() % 2) == 0) {
					gunSprite.setTexture(gunShot1);
				}
				else {
					gunSprite.setTexture(gunShot2);
				}
				target->Damage(13);
			}
		}
		else{
			hasTarget = false;
		}
	}
	else {
		if(state != State::PLACING)
		gunSprite.setTexture(gunna);
	}
	healthbar->Update(baseSprite.getPosition(), health, maxHealth);
}

sf::Vector2f Turret::GetPosition() {
	return baseSprite.getPosition();
}

void Turret::Damage(float damage) {
	health -= damage;
	if (health <= 0) {
		state = State::INACTIVE;
		baseSprite.setPosition(-1000, -1000);
		gunSprite.setPosition(-1000, -1000);
	}
}

void Turret::Regen(float deltaTime) {
	if (health < maxHealth && damageTimer <= 0) {
		health += 10 * deltaTime;
		
	}
	else if (damageTimer > 0) {
		damageTimer - deltaTime;
	}
}

sf::Sprite Turret::GetBaseSprite() {
	return baseSprite;
}

sf::Sprite Turret::GetGunSprite() {
	return gunSprite;
}

bool Turret::Active() {
	if (state == State::ACTIVE) {
		return true;
	}
	else {
		return false;
	}
}

bool Turret::Placing() {
	if (state == State::PLACING) {
		return true;
	}
	else {
		return false;
	}
}

void Turret::Placement(sf::Vector2f mousePos, bool _valid) {
	//Follow mouse cursor and turn green or red depending on valid placment points
	state = State::PLACING;
	gunSprite.setTexture(range);
	OriginateCenter(gunSprite);
	baseSprite.setPosition(mousePos);
	gunSprite.setPosition(mousePos);
	if (_valid) {
		baseSprite.setTexture(validSpot);
		valid = true;
	}
	else {
		valid = false;
		baseSprite.setTexture(invalidSpot);
	}
}

void Turret::Place(sf::Vector2f mousePos) {
	//Place turret if it is in a valid spot
	if (valid) {
		state = State::ACTIVE;
		baseSprite.setTexture(placed);
		baseSprite.setPosition(mousePos);
		gunSprite.setTexture(gunna);
		OriginateCenter(gunSprite);
		gunSprite.setPosition(mousePos);
		//placing.setPitch(0.6 + static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 2)));
		//placing.play();
	}
}

bool Turret::HasTarget() {
	return hasTarget;
}

void Turret::Target(Infected* inf) {
	target = inf;
	hasTarget = true;
}

sf::RectangleShape Turret::GetHealthbar() {
	return healthbar->GetBar();
}

bool Turret::isValid() {
	return valid;
}

void Turret::CancelPlacement() {
	state = State::INACTIVE;
	baseSprite.setPosition(-1000, -1000);
	gunSprite.setPosition(-1000, -1000);
}