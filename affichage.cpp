#include "affichage.hpp"


void Affichage::affiche_all() const{
            SDL_Rect dest;
            //On affiche la texture du sprite avec 
            for(Sprite* s : sprites){
                if(s->getOnScreen()){
                    
                    dest.x = s->getCoord()[0];
                    dest.y = s->getCoord()[1];

                    dest.w = s->getLargeur();
                    dest.h = s->getHauteur();

                    SDL_QueryTexture(s->getTexture(), NULL, NULL, &dest.w, &dest.h);
                    SDL_RenderCopy(renderer, s->getTexture(), NULL, &dest);
                }
                else{
                    //Enlever de la liste 
                }
            }
};