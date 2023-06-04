#ifndef VENERA_HPP
#define VENERA_HPP

#include "affichage.hpp"
#include "Mc.hpp"
#include "BasicSkeleton.hpp"
#include "SkeletonShooter.hpp"
#include "SpawnPoint.hpp"
#include "Joueur2.hpp"
#include "Input.hpp"
#include "AudioManager.hpp"

class SpawnPoint;

class Venera {
private :
	SDL_Renderer* renderer;
	SDL_Window* window;

	Stockeur* stockeur;
	// Mc* mc;
	// Joueur2* j2;
	AudioManager* audioM;
	
	Input* input;

	Affichage* afficheur;

	//Map map;
	
public :
	Venera();
	void initialisation();
	void pushBackEnemies(Enemies* en);

	void update();
};

#endif
