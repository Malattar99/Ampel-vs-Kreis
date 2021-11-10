#include "Simulation.h"
#include "CarProp.h"
void Simulation::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Kreuzverkehr", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(165);
	this->window->setVerticalSyncEnabled(false);

	this->window2 = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Kreisverkehr", sf::Style::Close | sf::Style::Titlebar);
	this->window2->setFramerateLimit(165);
	this->window2->setVerticalSyncEnabled(false);
}

void Simulation::initAuto()
{
	this->spawnTimerMax = 20.f;
}


void Simulation::initKreuzverkehr()
{
	if (!this->KreuzverkehrTex.loadFromFile("images/Kreuzverkehr.png"));
	{
		//std::cout << "kein hintergrund\n";
	}
	this->Kreuzverkehr.setTexture(this->KreuzverkehrTex);
}

void Simulation::initKreisverkehr()
{
	if (!this->KreisverkehrTex.loadFromFile("images/Kreisverkehr.png"));
	{
		//std::cout << "kein hintergrund\n";
	}
	this->Kreisverkehr.setTexture(this->KreisverkehrTex);
}

void Simulation::renderWorld()
{
	this->window->draw(this->Kreuzverkehr);
	this->window2->draw(this->Kreisverkehr);

}

bool Simulation::checkDistance(Autos obj_1, Autos obj_2) {
	float dist_x = obj_1.getPos().x - obj_2.getPos().x;
	float dist_y = obj_1.getPos().y - obj_2.getPos().y;

	float distance = sqrt(pow(dist_x, dist_x) + pow(dist_y, dist_y));

	if (distance < 80) {
		return false;
		//std::cout << "Abstand zu gering" << std::endl;
	}
	else
		return true;
}

Simulation::Simulation()
{
	this->initWindow();
	this->initAuto();
	this->initKreuzverkehr();
	this->initKreisverkehr();
}



Simulation::~Simulation()
{
	delete this->window;
	for (auto* i : this->autos)
	{
		delete i;
	}

	delete this->window2;
	for (auto* i : this->autoso)
	{
		delete i;
	}

}
//funktionen
void Simulation::run()
{
	this->createAmpel();
	std::cout << "create ampel" << std::endl;
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}

	while (this->window2->isOpen())
	{
		this->update();
		this->render();
	}
}

void Simulation::updateAuto()
{

	int rndValue = rand() % 10;
	//std::cout << rndValue << std::endl;
	int rndAnfahrt = rand() % 100;
	Direction spawn;
	if (rndAnfahrt < 15) {
		if (Functions::checkSpawnNorth(autos) == 0) {
			spawn = Direction::NORTH;
			//std::cout << "spawn auf nord" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}
	else if (rndAnfahrt < 50) {
		if (Functions::checkSpawnEast(autos) == 0) {
			spawn = Direction::EAST;
			//std::cout << "spawn auf ost" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}
	else if (rndAnfahrt < 65) {
		if (Functions::checkSpawnSouth(autos) == 0) {
			spawn = Direction::SOUTH;
			//std::cout << "spawn auf sued" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}
	else {
		if (Functions::checkSpawnWest(autos) == 0) {
			spawn = Direction::WEST;
			//std::cout << "spawn auf west" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}

	if (spawn != Direction::NOWHERE) {
		//rotes auto generieren
		if (rndValue < 2) // rotes Auto 20 %
		{
			this->autos.push_back(new Autos(spawn, Color::RED, Direction::EAST));
			//std::cout << "pushed back" << std::endl;
		}
		//Gelbes Auto generieren
		if (rndValue >= 2 && rndValue < 9) // gelbes Auto 70%
		{
			this->autos.push_back(new Autos(spawn, Color::YELLOW, Direction::WEST));
			//std::cout << "pushed back" << std::endl;
		}
		//Blaues Auto generieren
		if (rndValue == 9) // blaues Auto 10 %
		{
			this->autos.push_back(new Autos(spawn, Color::BLUE, Direction::EAST));
			//std::cout << "pushed back" << std::endl;
		}
	}
	if (rndAnfahrt < 15) {
		if (Functions::checkSpawnNorth1(autoso) == 0) {
			spawn = Direction::NORTH;
			//std::cout << "spawn auf nord" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}
	else if (rndAnfahrt < 50) {
		if (Functions::checkSpawnEast1(autoso) == 0) {
			spawn = Direction::EAST;
			//std::cout << "spawn auf ost" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}
	else if (rndAnfahrt < 65) {
		if (Functions::checkSpawnSouth1(autoso) == 0) {
			spawn = Direction::SOUTH;
			//std::cout << "spawn auf sued" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}
	else {
		if (Functions::checkSpawnWest1(autoso) == 0) {
			spawn = Direction::WEST;
			//std::cout << "spawn auf west" << std::endl;
		}
		else { spawn = Direction::NOWHERE; }
	}

	if (spawn != Direction::NOWHERE) {
		//rotes auto generieren
		if (rndValue < 2) // rotes Auto 20 %
		{
			this->autoso.push_back(new AutosO(spawn, Color::RED, Direction::EAST));
			//std::cout << "pushed back" << std::endl;
		}
		//Gelbes Auto generieren
		if (rndValue >= 2 && rndValue < 9) // gelbes Auto 70%
		{
			this->autoso.push_back(new AutosO(spawn, Color::YELLOW, Direction::WEST));
			//std::cout << "pushed back" << std::endl;
		}
		//Blaues Auto generieren
		if (rndValue == 9) // blaues Auto 10 %
		{
			this->autoso.push_back(new AutosO(spawn, Color::BLUE, Direction::EAST));
			//std::cout << "pushed back" << std::endl;
		}
	}
}



void Simulation::update()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}

	sf::Event u;
	while (this->window2->pollEvent(u))
	{
		if (u.Event::type == sf::Event::Closed)
			this->window->close();
		if (u.Event::KeyPressed && u.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}

	for (auto* car : this->autos)
	{
		car->update();
		//std::cout << "Auto moved" << std::endl;
	}

	for (auto* car2 : this->autoso)
	{
		car2->update();
		//std::cout << "Auto moved" << std::endl;
	}

	this->spawnTimer++;
	//Auto bewegen
	if (this->spawnTimer % 100 == 0) {
		this->updateAuto();
		//std::cout << "updateAuto\n";

	}
	if (this->spawnTimer % 100 == 0) {
		this->updateAuto();
	}

	if (this->spawnTimer % 1000 == 0) {
		this->updateAllAmpel();
	}


	// if (this->spawnTimer == 500 || this->spawnTimer == 1500) {
	// 	this->updateAmpel1();
	// }
	// if (this->spawnTimer == 530 || this->spawnTimer == 1530) {
	// 	this->updateAmpel2();
	// }
	// if (this->spawnTimer == 540 || this->spawnTimer == 1540) {
	// 	this->updateAmpel3();
	// }
	// if (this->spawnTimer == 570 || this->spawnTimer == 1570) {
	// 	this->updateAmpel4();
	// }
	// if (this->spawnTimer == 930 || this->spawnTimer == 1930) {
	// 	this->updateAmpel5();
	// }
	// if (this->spawnTimer == 960 || this->spawnTimer == 1960) {
	// 	this->updateAmpel6();
	// }
	// if (this->spawnTimer == 970 || this->spawnTimer == 1970) {
	// 	this->updateAmpel7();
	// }
	// if (this->spawnTimer == 1000 || this->spawnTimer == 2000) {
	// 	this->updateAmpel8();
	// }
}

void Simulation::render() {
	this->window->clear();
	this->window2->clear();
	this->renderWorld();
	for (Ampel* far : this->ampeln)
	{
		far->render(*this->window);
	}

	for (auto* car : this->autos)
	{
		car->render(*this->window);
	}

	for (auto* car2 : this->autoso)
	{
		car2->render(*this->window2);
	}



	this->window->display();
	this->window2->display();
}
void Simulation::createAmpel()
{
	this->ampeln.push_back(new Ampel(Ampel_Seite::OBEN, Ampel_Farbe::RED));
	this->ampeln.push_back(new Ampel(Ampel_Seite::UNTEN, Ampel_Farbe::RED));
	this->ampeln.push_back(new Ampel(Ampel_Seite::RECHTS, Ampel_Farbe::GREEN));
	this->ampeln.push_back(new Ampel(Ampel_Seite::LINKS, Ampel_Farbe::GREEN));

}

// schaltet alle Ampeln einen Zyklus weiter
void Simulation::updateAllAmpel() {
	std::cout << "update all traffic lights" << std::endl;
	for (int i = 0; i < this->ampeln.size(); i++) {
		this->updateAmpel(i);
	}
}

// schaltet die Ampel mit dem Index 'index' einen Zyklus weiter
void Simulation::updateAmpel(int index) {
	this->ampeln[index]->cycle();
}