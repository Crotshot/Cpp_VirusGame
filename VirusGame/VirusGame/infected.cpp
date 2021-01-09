#include "pch.h"
#include "infected.h"
#include "textureHolder.h"
#include "methods.h"

Infected::Infected() {}

Infected::Infected(Infected &infected) {
	this->infectedTexture = TextureHolder::GetTexture("Assets/Graphics/Infected.png");
	this->corpseTexture = TextureHolder::GetTexture("Assets/Graphics/Infected_Corpse.png");
	this->state = State::NOTSPAWNED;
}

Infected::~Infected() {
	delete healthbar;
	healthbar = NULL;
}

void Infected::GenerateInfected(/*sf::SoundBuffer infBuffer*/) {
	maxHealth = 80 + rand() % 40;
	health = maxHealth;
	maxSpeed = 24 + rand() % 10;
	speed = maxSpeed;
	infectedSprite.setTexture(infectedTexture);
	infectedSprite.setPosition(-1000,-1000);
	healthbar = new Healthbar(*healthbar, sf::Color::Red, 20, 3);

	//death.setBuffer(infBuffer);
	//this->death.setVolume(0.8);
}

void Infected::GenerateInfectedSpawn() {
	maxHealth = 80 + rand() % 40;
	health = maxHealth;
	maxSpeed = 24 + rand() % 10;
	speed = maxSpeed;
	infectedSprite.setTexture(infectedTexture);
	infectedSprite.setPosition(-1000, -1000);
	healthbar = new Healthbar(*healthbar, sf::Color::Red, 20, 3);
}

void Infected::Update(float time, Core& core) {
	if (canMove && state == State::ALIVE) {
		float x = 0, y = 0, ratio = 0;
		x = core.GetPosition().x - infectedSprite.getPosition().x;
		y = core.GetPosition().y - infectedSprite.getPosition().y;

		ratio = sqrt(pow(x, 2)) + sqrt(pow(y, 2));

		x = speed * time * (x / ratio);
		y = speed * time * (y / ratio);
		infectedSprite.setPosition(infectedSprite.getPosition().x + x, infectedSprite.getPosition().y + y);

		float angle = (atan2(core.GetPosition().y - infectedSprite.getPosition().y,
			infectedSprite.getPosition().x - core.GetPosition().x)
			* 180) / 3.141;

		infectedSprite.setRotation(angle + 1.5708);
		healthbar->Update(infectedSprite.getPosition(), health, maxHealth);
	}
}

float Infected::GetHealth() {
	return health;
}

void Infected::Damage(float damage) {
	health -= damage;
	if (health <= 0) {
		state = State::DEAD;
		infectedSprite.setTexture(corpseTexture);
		speed = 0;
		canMove = false;
		//death.setPitch(0.6 + static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 2)));
		//death.play();
	}
}

Vector2f Infected::GetPosition() {
	return infectedSprite.getPosition();
}

void Infected::Spawn(sf::Vector2f hole) {
	OriginateCenter(infectedSprite);
	GenerateInfectedSpawn();
	state = State::ALIVE;
	canMove = true;
	infectedSprite.setTexture(infectedTexture);
	infectedSprite.setPosition(hole);
}

void Infected::Contact(int touching) {
	if ((touching == 0)) {
		speed = maxSpeed; //Touching nothing
	}
	else if (touching == 1) {
		speed = maxSpeed/3; //Touching barbed wire
	}
	else {
		speed = 0; //Touching a building
	}
}

bool Infected::Alive() {
	if (state == State::ALIVE) {
		return true;
	}
	else {
		return false;
	}
}

bool Infected::Dead() {
	if (state == State::DEAD) {
		return true;
	}
	else {
		return false;
	}
}

sf::Sprite Infected::GetSprite() {
	return infectedSprite;
}

sf::RectangleShape Infected::GetHealthbar() {
	return healthbar->GetBar();
}