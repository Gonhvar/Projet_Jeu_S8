#ifndef VENERA_HPP
#define VENERA_HPP

#include "affichage.hpp"
#include "Mc.hpp"
#include "BasicSkeleton.hpp"
#include "SpawnPoint.hpp"

class SpawnPoint;

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

class Venera {
private :
	Mc* mc;
	std::vector<Enemies*> enemies;
	std::vector<Drop*> drop; // On fait la distinction entre les Enemies et les Drop car les Enemies prennent des décisions.
							// ça évite de faire des cast.
	//Map map;
	std::vector<SpawnPoint*> spawnPoints;


public : // J'ai mis ça public parce que sinon on ne pouvait pas y accéder dans le main. On réglera ça plus tard.
	App* app;
	Affichage* afficheur;
	
public :
	Venera();
	void initialisation();
	void pushBackEnemies(Enemies* en);

	void update();
};

#endif