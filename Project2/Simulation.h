#pragma once
#include"Autos.h"
#include"AutosO.h"
#include "Functions.h"
#include "Ampel.h"
class Simulation
{
private:
	sf::RenderWindow* window;
	sf::RenderWindow* window2;
	//Autos
	//Auto rot
	int spawnTimer;
	int spawnTimerMax;

	//Autos im Kreuzverkehr
	std::vector<Autos*> autos;
	std::vector<Ampel*> ampeln;

	//Autos im kreisverkehr
	std::vector<AutosO*> autoso;
	//Hintergrund
	sf::Texture KreuzverkehrTex;
	sf::Sprite Kreuzverkehr;
	sf::Texture KreisverkehrTex;
	sf::Sprite Kreisverkehr;

	bool checkDistance(Autos obj_1, Autos obj_2);
	void initWindow();
	void initAuto();
	void initKreuzverkehr();
	void initKreisverkehr();
	void renderWorld();

public:
	Simulation();
	virtual ~Simulation();
	
	//funktionen
	void run();
	void updateAllAmpel();
	void updateAuto();
	void updateAmpel(int index);
	void update();
	void render();
	void createAmpel();
};