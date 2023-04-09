#include "affichage.hpp"

SDL_Texture* Affichage::visit(Sprite& s, std::string& spriteName){
        
    // On vérifie si l'image n'a pas déjà été chargée
    imIterator = imageChargees.find('b');
    if (imIterator != imageChargees.end()) { // Déjà chargée
        return imIterator->second;
    }



    // On la charge et on la stocke dans imageChargees
    SDL_Texture* justLoaded = loadTexture(PATH_TO_TEXTURE_FOLDER + spriteName + imageFormat);
    imageChargees[spriteName] = justLoaded;

    sprites.push_back(s);
};

void Affichage::enleveSprite(const Sprite& s) {
    remove(sprites.begin(), sprites.end(), &s);
}

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