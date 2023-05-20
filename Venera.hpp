#ifndef VENERA_HPP
#define VENERA_HPP

#include "affichage.hpp"
#include "Mc.hpp"
#include "BasicSkeleton.hpp"
#include "SpawnPoint.hpp"
#include "Joueur2.hpp"

class SpawnPoint;

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

class Venera {
private :
	Stockeur* stockeur;
	Mc* mc;
	Joueur2* j2;
	Affichage* afficheur;

	//Map map;
	std::vector<SpawnPoint*> spawnPoints;


public : // J'ai mis ça public parce que sinon on ne pouvait pas y accéder dans le main. On réglera ça plus tard.
	App* app;
	
public :
	Venera();
	void initialisation();
	void pushBackEnemies(Enemies* en);

	void update();
};

#endif
