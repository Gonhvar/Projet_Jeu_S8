#ifndef VENERA_HPP
#define VENERA_HPP

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

class affichage {
    private :
    std::vector<Sprite> sprites;
    SDL_Renderer *renderer;

    public :
        affichage(SDL_Renderer *rend) : renderer(rend){

        };

        void visit(Sprite s) const{
            sprites.push_back(s);
        };

        void affiche_all() const{
            SDL_Rect dest;
        //On affiche la texture du sprite avec 
            for(Sprite s : sprites){
                if(onScreen){

                    dest.x = s.coord[0];
                    dest.y = s.coord[1];

                    dest.w = s.largeur;
                    dest.h = s.hauteur;

                    SDL_QueryTexture(s.texture, NULL, NULL, &dest.w, &dest.h);
                    SDL_RenderCopy(renderer, texture, NULL, &dest);
                }
            }
        };
};

#endif