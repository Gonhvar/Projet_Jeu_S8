#ifndef VENERA_HPP
#define VENERA_HPP
#include <stdio.h>
#include <stdint.h>
#include <iostream>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//class Affichage;
#include "affichage.hpp"

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

class Venera {
public :
	App* app;
	Affichage* afficheur;

public :
	Venera();

	void waitquit();  
};

#endif