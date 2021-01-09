#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <time.h>

#include "textureHolder.h";
#include "core.h"
#include "infected.h"
#include "spawner.h"
#include "methods.h"
#include "barbedWire.h"
#include "turret.h"

#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>


/*1
//TEST Turret destroyed sound
*/

using namespace sf;

int main(){
	TextureHolder holder;

	enum class State { Pause, Play };
	State gameState = State::Pause;

	//Screen Setup
	int xWidth = 1280, yWidth = 1080;
	VideoMode vm(xWidth, yWidth);
	RenderWindow window(vm, "Protect the Core V 1.0", Style::Close);
	View mainView(sf::FloatRect(0, 0, xWidth, yWidth));
	window.setMouseCursorVisible(false);

	//Gameover sprite
	Sprite goSprite;
	goSprite = Sprite(TextureHolder::GetTexture("Assets/Graphics/YOULOSE.png"));
	OriginateCenter(goSprite);
	goSprite.setPosition(640, 540);
	bool gameOver = false;

	//Cursor
	Vector2f mouseScreenPosition;
	Sprite cursorSprite;
	cursorSprite = Sprite(TextureHolder::GetTexture("Assets/Graphics/Cursor.png"));
	OriginateCenter(cursorSprite);
	cursorSprite.setScale(1.3, 1.3);
	//Setting Backgorund
	Texture textureBackground = TextureHolder::GetTexture("Assets/Graphics/BackGround.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//Creation of base core
	Core* core = new Core();
	core->GenerateNewCore(1000);
	core->SetPosition(540, 540);
	srand(time(0));

	//Clock
	Clock clock;

	//Game time
	Time time;

	//Get sounds
	sf::SoundBuffer barbedBuffer, placedBuffer; 


	barbedBuffer.loadFromFile("Assets/Sounds/BarbedPlace.wav");
	placedBuffer.loadFromFile("Assets/Sounds/TurretPlace.wav");


	sf::Sound barbed, placed;
	barbed.setBuffer(barbedBuffer);
	barbed.setVolume(2);
	placed.setBuffer(placedBuffer);
	placed.setVolume(2);

	//Generate objects
	Infected* horde[2500];
	Infected* inf = new Infected();
	for (int i = 0; i < 2500; i++) {
		inf = new Infected(*inf);
		horde[i] = inf;
		horde[i]->GenerateInfected(/*deathBuffer*/);
	}


	Spawner* holes[50];
	Spawner* hole = new Spawner();
	for (int i = 0; i < 50; i++) {
		hole = new Spawner(*hole);
		holes[i] = hole;
	}

	int turretIndex = 0;
	Turret* turrets[75];
	Turret* turret = new Turret();
	for (int i = 0; i < 75; i++) {
		turret = new Turret(*turret);
		turrets[i] = turret;
		turrets[i]->GenerateTurret(600);
	}

	int barbedIndex = 0;
	BarbedWire* barbedWires[250];
	BarbedWire* barbedWire = new BarbedWire();
	for (int i = 0; i < 250; i++) {
		barbedWire = new BarbedWire(*barbedWire);
		barbedWires[i] = barbedWire;
		barbedWires[i]->GenerateBarbedWire(120);
	}

	//Load font
	sf::Font font;
	font.loadFromFile("Assets/Fonts/ZOMBIE.TTF");

	//Money, Time, Kills and difficulty scaling
	int kills = 0, money = 190, //Starter cash
		aliveThisFrame = 0, aliveLastFrame = 0,
		difficulty = 0, difficultyLastFrame = 0,
		spawnerIndex = 0, hordeIndex = 0;

	float timeSurvivedSeconds = 0, timeSurvivedMinutes = 0, survivedTimeTotal = 0, spawnerTick = 5, spawnerTickTimer = 0;
	String mins, secs;
	sf::Text timeSurvivedText/*1125, 700*/, killsText/*1125, 825*/, moneyText/*1125, 575*/;

	timeSurvivedText.setCharacterSize(40);
	killsText.setCharacterSize(40);
	moneyText.setCharacterSize(40);

	timeSurvivedText.setPosition(1125, 700);
	killsText.setPosition(1125, 825);
	moneyText.setPosition(1125, 575);

	timeSurvivedText.setFont(font);
	killsText.setFont(font);
	moneyText.setFont(font);

	timeSurvivedText.setFillColor(sf::Color::Yellow);
	killsText.setFillColor(sf::Color::Yellow);
	moneyText.setFillColor(sf::Color::Yellow);

	bool placingTurret = false, placingBarbed = false, toggleHealthbars = false;

	//Game Loop
	while (window.isOpen()) {
		Time dt = clock.restart();
		time = dt;
		float dtAsSeconds = dt.asSeconds();

		mouseScreenPosition = sf::Vector2f(Mouse::getPosition(window));
		cursorSprite.setPosition(mouseScreenPosition.x, mouseScreenPosition.y);

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Num0)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Num8)) {
			gameState = State::Play;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num9)) {
			gameState = State::Pause;
		}

		if (core->GetHealth() <= 0) {
			gameOver = true;
		}

		//Calculations and Collisions
		if (gameState == State::Play && !gameOver) {
			//Play Game
			timeSurvivedSeconds += dtAsSeconds;
			survivedTimeTotal += dtAsSeconds;
			if (timeSurvivedSeconds >= 60) {
				timeSurvivedSeconds -= 60;
				timeSurvivedMinutes++;
			}
			if (timeSurvivedMinutes < 10) {
				mins = "0" + std::to_string((int)timeSurvivedMinutes);
			}
			else {
				mins = std::to_string((int)timeSurvivedMinutes);
			}

			if (timeSurvivedSeconds < 10) {
				secs = "0" + std::to_string((int)timeSurvivedSeconds);
			}
			else {
				secs = std::to_string((int)timeSurvivedSeconds);
			}
			///////////////////////////////////SPAWNING/////////////////////////////////
			if (survivedTimeTotal > (difficulty * 20)) {
				difficulty++;
			}
			if (difficultyLastFrame < difficulty) {
				if (spawnerIndex < 50) {
					holes[spawnerIndex]->GenerateSpawner();
					spawnerIndex++;
					if (spawnerTick > 0.05) {
						spawnerTick -= 0.09;
					}
				}
			}

			difficultyLastFrame = difficulty;

			if (spawnerTickTimer < spawnerTick) {
				spawnerTickTimer += dtAsSeconds;
			}
			else {
				spawnerTickTimer = 0;
				if (difficulty / 3 == 0) {
					horde[hordeIndex]->Spawn(holes[rand() % spawnerIndex]->GetPosition());
					hordeIndex++;
				}
				for (int i = 0; i < difficulty / 3; i++) {
					horde[hordeIndex]->Spawn(holes[rand() % spawnerIndex]->GetPosition());
					hordeIndex++;
					if (hordeIndex > 2499) {
						hordeIndex = 0;
					}
				}
			}

			////////////////////////////////////////////////////////////////////////////
			
			//Update text
			timeSurvivedText.setString(mins + "-" + secs);
			killsText.setString(std::to_string(kills));
			moneyText.setString(std::to_string(money));

			if (Keyboard::isKeyPressed(Keyboard::Num1)) {
				placingTurret = true;
				placingBarbed = false;
				if (turretIndex > 74) {
					turretIndex = 0;
				}

				if (barbedWires[barbedIndex]->Placing()) {
					barbedWires[barbedIndex]->CancelPlacement();
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Num2)) {
				placingBarbed = true;
				placingTurret = false;
				if (barbedIndex > 249) {
					barbedIndex = 0;
				}

				if (turrets[turretIndex]->Placing()) {
					turrets[turretIndex]->CancelPlacement();
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Num3)) {
				placingBarbed = false;
				placingTurret = false;

				if (turrets[turretIndex]->Placing()) {
					turrets[turretIndex]->CancelPlacement();
				}
				if (barbedWires[barbedIndex]->Placing()) {
					barbedWires[barbedIndex]->CancelPlacement();
				}
			}

			if (placingTurret == true) {
				//Can only place between 225,225 and 860,860
				if (mouseScreenPosition.x < 225 || mouseScreenPosition.x > 860 || mouseScreenPosition.y < 225 || mouseScreenPosition.y > 860 || money < 100) {
					turrets[turretIndex]->Placement(mouseScreenPosition, false);
				}
				else {
					for (int i = 0; i < 50; i++) {
						if (turrets[turretIndex] == turrets[i])
							continue;
						if (SquareCollision(turrets[turretIndex]->GetBaseSprite(), turrets[i]->GetBaseSprite())) {
							turrets[turretIndex]->Placement(mouseScreenPosition, false);
							break;
						}
						if (SquareCollision(turrets[turretIndex]->GetBaseSprite(), core->GetSprite())) {
							turrets[turretIndex]->Placement(mouseScreenPosition, false);
							break;
						}
						else {
							turrets[turretIndex]->Placement(mouseScreenPosition, true);
						}
					}
				}
			}
			else if (placingBarbed == true) {
				//Can only place between 225,225 and 860,860
				if (mouseScreenPosition.x < 100 || mouseScreenPosition.x > 980 || mouseScreenPosition.y < 100 || mouseScreenPosition.y > 980 || money < 35) {
					barbedWires[barbedIndex]->Placement(mouseScreenPosition, false);
				}
				else {
					for (int i = 0; i < 50; i++) {
						if (barbedWires[barbedIndex] == barbedWires[i])
							continue;
						if (SquareCollision(barbedWires[barbedIndex]->GetSprite(), turrets[i]->GetBaseSprite())) { //Cant place barbed wire on turrets
							barbedWires[barbedIndex]->Placement(mouseScreenPosition, false);
							break;
						}
						if (SquareCollision(barbedWires[barbedIndex]->GetSprite(), core->GetSprite())) {
							barbedWires[barbedIndex]->Placement(mouseScreenPosition, false);
							break;
						}
						else {
							barbedWires[barbedIndex]->Placement(mouseScreenPosition, true);
						}
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (placingTurret && !Keyboard::isKeyPressed(Keyboard::Num1) && money >= 100 && turrets[turretIndex]->isValid()) {
					turrets[turretIndex]->Place(mouseScreenPosition);
					turretIndex++;
					money -= 100;
					placingTurret = false;
					placed.setPitch(0.6 + static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 2)));
					placed.play();
				}
				else if (placingBarbed && !Keyboard::isKeyPressed(Keyboard::Num2) && money >= 35 && barbedWires[barbedIndex]->isValid()) {
					barbedWires[barbedIndex]->Place(mouseScreenPosition);
					barbedIndex++;
					money -= 35;
					placingBarbed = false;
					barbed.setPitch(0.6 + static_cast <float> (rand()) / ((static_cast <float> (RAND_MAX) * 2)));
					barbed.play();
				}
			}

			for (int j = 0; j < 50; j++) {
				if (turrets[j]->Active() && !turrets[j]->HasTarget()) {
					for (int i = 0; i < 2500; i++) {
						if (horde[i]->Alive() && CircularCollision(horde[i]->GetSprite(),turrets[j]->GetPosition() ,125) ){
							turrets[j]->Target(horde[i]);
							break;
						}
					}
				}
				turrets[j]->Update(dtAsSeconds);
			}

			for (int k = 0; k < 250; k++) {
				barbedWires[k]->Update();
			}

			aliveThisFrame = 0;
			for (int i = 0; i < 2500; i++) {
				if (horde[i]->Alive()) {
					aliveThisFrame++;
					if (SquareCollision(horde[i]->GetSprite(), core->GetSprite())) {
						horde[i]->Contact(2);
						core->Damage(dtAsSeconds * 2);
					}
					else {
						horde[i]->Contact(0);
						for (int k = 0; k < 250; k++) {
							if (barbedWires[k]->Active()) {
								if (SquareCollision(horde[i]->GetSprite(), barbedWires[k]->GetSprite())) {
									horde[i]->Contact(1);
									horde[i]->Damage(0.1 * dtAsSeconds);
									barbedWires[k]->Damage(0.05 * dtAsSeconds);
								}
							}
						}
						for (int j = 0; j < 50; j++) {
							if (turrets[j]->Active()) {
								if (SquareCollision(horde[i]->GetSprite(), turrets[j]->GetBaseSprite())) {
									horde[i]->Contact(2);
									turrets[j]->Damage(dtAsSeconds * 2);
								}
							}
						}
					}
				}
				horde[i]->Update(dtAsSeconds, *core);
			}

			if (aliveThisFrame < aliveLastFrame) {
				kills += (aliveLastFrame - aliveThisFrame);
				money += 4 + rand() % 4;						//Get 4-7 money per kill
			}
			aliveLastFrame = aliveThisFrame;

			core->Update(dtAsSeconds);
		/*-----------------------------------------------------------*/
		}
		else {
			//Pause Game
			dt = clock.restart();
		}
		//Render Screen -> Displays graphics every frame
		window.clear();
		window.draw(spriteBackground);
		window.draw(core->GetSprite());
		window.draw(core->GetHealthbar());
		/*-------------------------TEST CODE-------------------------*/
		for (int i = 0; i < 2500; i++) {
			if (horde[i]->Dead()) {
				window.draw(horde[i]->GetSprite());
			}

		}

		for (int i = 0; i < 50; i++) {
			if (holes[i]->Active()) {
				window.draw(holes[i]->GetSprite());
			}
		}

		for (int i = 0; i < 250; i++) {
			if (barbedWires[i]->Active()) {
				window.draw(barbedWires[i]->GetSprite());
			}
		}

		for (int i = 0; i < 2500; i++) {
			if (horde[i]->Alive()) {
				window.draw(horde[i]->GetSprite());
			}
		}

		for (int i = 0; i < 50; i++) {
			if (turrets[i]->Active()) {
				window.draw(turrets[i]->GetBaseSprite());
				window.draw(turrets[i]->GetGunSprite());
				window.draw(turrets[i]->GetHealthbar());
			}
		}

		for (int i = 0; i < 250; i++) {
			if (barbedWires[i]->Active()) {
				window.draw(barbedWires[i]->GetHealthbar());
			}
		}

		for (int i = 0; i < 2500; i++) {
			if (horde[i]->Alive()) {
				window.draw(horde[i]->GetHealthbar());
			}
		}
		/*-----------------------------------------------------------*/

		for (int i = 0; i < 50; i++) {
			if (turrets[i]->Placing()) {
				window.draw(turrets[i]->GetBaseSprite());
				window.draw(turrets[i]->GetGunSprite());
				break;
			}

		}
		for (int i = 0; i < 250; i++) {
			if (barbedWires[i]->Placing()) {
				window.draw(barbedWires[i]->GetSprite());
			}
		}

		window.draw(timeSurvivedText);
		window.draw(killsText);
		window.draw(moneyText);

		if (gameOver) {
			window.draw(goSprite);
		}

		window.draw(cursorSprite);
		window.display();
	}

	delete core;
	core = NULL;

	return 0;
}