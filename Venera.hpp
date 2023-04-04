#ifndef VENERA_HPP
#define VENERA_HPP
#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "affichage.hpp"

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

class Venera {
    public :
        Venera(){};

        void waitquit(){   
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        exit(0);
                        break;

                    default:
                        break;
                }
            }
        };
        
};

#endif