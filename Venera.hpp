#ifndef VENERA_HPP
#define VENERA_HPP
#include <stdio.h>
#include <stdint.h>
#include <iostream>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "affichage.hpp"
#include "Mc.hpp"
#include "BasicSkeleton.hpp"



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

public : // J'ai mis ça public parce que sinon on ne pouvait pas y accéder dans le main. On réglera ça plus tard.
	App* app;
	Affichage* afficheur;
	
public :
	Venera();
	void initialisation();
	void keyboard_event();

	void update();
};

#endif