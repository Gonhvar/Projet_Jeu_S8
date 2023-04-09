#ifndef VENERA_HPP
#define VENERA_HPP
#include <stdio.h>
#include <stdint.h>
#include <iostream>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "affichage.hpp"
#include "Entite.hpp"
#include "Mc.hpp"

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

class Venera {
public : // J'ai mis ça public parce que sinon on ne pouvait pas y accéder dans le main. On réglera ça plus tard.
	App* app;
	Affichage* afficheur;

public :
	Venera();

	void waitquit();  
};

#endif