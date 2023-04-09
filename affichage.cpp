#include "affichage.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Affichage::Affichage(SDL_Renderer* rend) : renderer(rend){
	camPos[0] = 0;
	camPos[1] = 0;
	zoom = 1;
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Affichage::visit(Sprite* s, std::string& spriteName){
	// Ajoute s dans sprites et va chercher ses textures
	SDL_Texture* textureChargee;
	// On vérifie si l'image n'a pas déjà été chargée
	imIterator = imageChargees.find(spriteName);
	if (imIterator != imageChargees.end()) { // Déjà chargée
		textureChargee = imIterator->second;
	}
	else { // Sinon on la charge et on la stocke dans imageChargees
		const char* filename = (PATH_TO_TEXTURE_FOLDER + spriteName + imageFormat).c_str();
		textureChargee = IMG_LoadTexture(renderer, filename);
		
		// if (loadeing error) do something
		// else :
		imageChargees[spriteName] = textureChargee;
	}

	stt* aPush = new stt();
	aPush->sprite = s;
	aPush->textures.push_back(textureChargee);

	sprites.push_back(*aPush);
};

void Affichage::enleveSprite(const Sprite& s) {
	//remove(sprites.begin(), sprites.end(), &s);
}

void Affichage::affiche_all() const{
	SDL_RenderClear(renderer); // ça n'est peut-être pas nécessaire mais la doc conseille de le faire

	SDL_Rect dest;
	//On affiche la texture du sprite avec 
	for(stt s : sprites){
		if(s.sprite->getOnScreen()){
			// position relative du Sprite par rapport à la caméra
			dest.x = (s.sprite->getCoord()[0] - camPos[0]) * zoom;
			dest.y = (s.sprite->getCoord()[1] - camPos[1]) * zoom;

			dest.w = s.sprite->getLargeur() * zoom;
			dest.h = s.sprite->getHauteur() * zoom;

			SDL_QueryTexture(s.textures[0], NULL, NULL, &dest.w, &dest.h);
			SDL_RenderCopy(renderer, s.textures[0], NULL, &dest);
		}
		else{
			//Enlever de la liste 
		}
	}
	SDL_RenderPresent(renderer); // Met à jour l'écran avec le backbuffer du renderer
};