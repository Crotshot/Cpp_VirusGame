#include "pch.h"
#include "core.h"
#include "textureHolder.h"
#include "methods.h"

Core::Core() {						//Default Constructor
}

Core::Core(Core &core) {			//Copy Constructor
	core.GenerateNewCore(5000);
}

Core::~Core() {
	delete healthbar;
	healthbar = NULL;
}

float Core::GetHealth() {
	return health;
}

void Core::Damage(float damage) {
	if (health > 0) {
		health -= damage;
		damageTimer = 4;
	}
}

sf::Vector2f Core::GetPosition() {
	return coreSprite.getPosition();
}

void Core::SetPosition(int x, int y) {
	coreSprite.setPosition(x,y);
}

void Core::Regen(float deltaTime) {
	if (health < maxHealth && damageTimer  <= 0) {
		health += 10 * deltaTime;
	}
	else if(damageTimer > 0){
		damageTimer - deltaTime;
	}
}

void Core::GenerateNewCore(float hp) {
	coreSprite = Sprite(TextureHolder::GetTexture("Assets/Graphics/Core.png"));
	OriginateCenter(coreSprite);
	maxHealth = hp;
	health = maxHealth; //Change back later
	damageTimer = 0;
	SetPosition(0, 0);
	healthbar = new Healthbar(*healthbar, sf::Color::Green, 150, 10);
}

void Core::Update(float time) {
	if (damageTimer > 0) {
		damageTimer -= time;
	}
	else if(health  < maxHealth){
		health += time * 2.5;
	}

	healthbar->Update(coreSprite.getPosition(),health,maxHealth);
}

Sprite Core::GetSprite() {
	return coreSprite;
}

sf::RectangleShape Core::GetHealthbar() {
	return healthbar->GetBar();
}