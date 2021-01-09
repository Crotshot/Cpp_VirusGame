#include "pch.h"
#include "spawner.h"
#include "textureHolder.h"
#include "methods.h"

Spawner::Spawner() {}

Spawner::Spawner(Spawner &spawner) {
	spawnerState = State::INACTIVE;
	spawnerSprite = Sprite(TextureHolder::GetTexture("Assets/Graphics/Hole.png"));
	spawnerSprite.setPosition(-1000, -1000);
}

Spawner::~Spawner() {}

void Spawner::GenerateSpawner() {
	OriginateCenter(spawnerSprite);

	lifetime = rand() % (45, 75);
	//Set position of spawner only around the edge of map
	int side = rand() % 4;								//Along 150, 930 lines

	if (side == 0) {		//TOP
		spawnerSprite.setPosition(150 + rand() % 781,150);
	}
	else if(side == 1){		//BOTTOM 
		spawnerSprite.setPosition(150 + rand() % 781, 930);
	}
	else if (side == 2){	//LEFT
		spawnerSprite.setPosition(150, 150 + rand() % 781);
	}
	else {					//Right
		spawnerSprite.setPosition(930, 150 + rand() % 781);
	}

	float angle = (atan2(rand() % 1000 - rand() % 1000,
		rand() % 1000 - rand() % 1000)
		* 180) / 3.141;

	spawnerSprite.setRotation(angle);

	spawnerState = State::ACTIVE;
}

void Spawner::Return() {
	if (spawnerState == State::ACTIVE) {
		if (lifetime < 0) {
			spawnerState == State::INACTIVE;
			spawnerSprite.setPosition(-1000, -1000);
		}
	}
}

Vector2f Spawner::GetPosition() {
	return spawnerSprite.getPosition();
}

bool Spawner::Active() {
	if (spawnerState == State::ACTIVE) {
		return true;
	}
	else {
		return false;
	}
}

sf::Sprite Spawner::GetSprite() {
	return spawnerSprite;
}