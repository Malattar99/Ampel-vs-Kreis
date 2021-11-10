#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include "CarProp.h"



class Ampel
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	void initTexture(Ampel_Farbe f);
	void initSprite();


public:
	Ampel(Ampel_Seite seite, Ampel_Farbe ampel_farbe);
	virtual ~Ampel();
	Ampel_Farbe color;
	//zeit funktion, clock zählt sekunden auf
	sf::Clock clock;
	sf::Time elapsed1 = clock.getElapsedTime();
	void initClock();

	bool ampel_up;
	bool Ampel_up();
	
	void render(sf::RenderTarget& target);
	void cycle();
};


