#ifndef VENERA_HPP
#define VENERA_HPP

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

class Affichage {
    protected :
    std::vector<Sprite*> sprites;
    SDL_Renderer *renderer;

    public :
        Affichage(SDL_Renderer *rend) : renderer(rend){
            
        };

        void visit(Sprite* s){
            sprites.push_back(s);
        };

        void affiche_all() const;
};

#endif