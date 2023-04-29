#include "affichage.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Affichage::Affichage(){};

Affichage::Affichage(SDL_Renderer* rend) : renderer(rend) {
	camPos[0] = 0;
	camPos[1] = 0;
	zoom = 1;

	// Sprite::afficheur = this;

	noTexture = IMG_LoadTexture(renderer, NO_TEXTURE_FOUND);
	if (!noTexture) { // L'image n'a pas pu être chargée. On prend la texture par défaut.
		std::cout << "Erreur de chargement de noTexture : ça sans pas bon là" << std::endl;
	}
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Affichage::setZoom(float z) {
	zoom = z;
}

void Affichage::setCamPos(float x, float y) {
	camPos[0] = x;
	camPos[1] = y;
}

//void Affichage::visit(Sprite* s, std::string& spriteName, uint8_t nbEtats, std::vector<uint8_t>& nbFrameParEtat) {
void Affichage::visit(Sprite* s, const States* states) {
	// Ajoute s dans sprites et va chercher ses textures

	// On vérifie si l'image n'a pas déjà été chargée
	imIterator = imageChargees.find(states->spriteName);
	if (imIterator != imageChargees.end()) { // Déjà chargée
		s->setTexture(imIterator->second);
		std::cout << "Image de " << states->spriteName << " déjà chargée :)" << std::endl;
	}
	else { // Sinon on la charge et on la stocke dans imageChargees
		SDL_Texture* textureChargee;
		TexturePack* newTexture = new TexturePack(states->nbEtats);
		std::cout << "taille de la nouvelle texture : " << (*newTexture).size() << std::endl;
		for (int etat=0; etat<states->nbEtats; etat++) {
			(*newTexture)[etat].resize(states->nbFrameParEtat[etat]);
			std::cout << "taille de l'état " << etat << " : " << (*newTexture)[etat].size() << std::endl;
			for (int frame=0; frame<states->nbFrameParEtat[etat]; frame++) {
				std::string pathComplet = PATH_TO_TEXTURE_FOLDER + states->spriteName + "/" + std::to_string(etat) + "/" + std::to_string(frame) + imageFormat;
				const char* filename = pathComplet.c_str();
				
				textureChargee = IMG_LoadTexture(renderer, filename);
				if (!textureChargee) { // L'image n'a pas pu être chargée. On prend la texture par défaut.
					std::cout << "Erreur de chargement de " << states->spriteName << " ---> a ete cherche a : " << pathComplet << std::endl;
					textureChargee = noTexture;
				}
				(*newTexture)[etat][frame] = textureChargee;
			}
		}
		s->setTexture(newTexture);
		
		imageChargees[states->spriteName] = newTexture;
	}

	sprites.push_back(s);
};

void Affichage::enleveSprite(const Sprite& s) {
	//remove(sprites.begin(), sprites.end(), &s);
}

void Affichage::update(){
	//enemiesUpdate(); ça ne devrait pas être là
	affiche_all();
}


void Affichage::affiche_all() const{
	SDL_RenderClear(renderer);
	
	//std::cout << "affichage de : " << sprites[0] << " dont le nom est : " << sprites[0]->name << std::endl;
	//std::cout << "affichage de : " << sprites[1] << " dont le nom est : " << sprites[1]->name << std::endl;
	
	SDL_Rect dest;
	// On affiche la texture du sprite avec 
	for(Sprite* s : sprites){
		std::cout << "affichage de : " << s << " dont le nom est : " << s->name << std::endl;
		if(s->getOnScreen()){
			// position relative du Sprite par rapport à la caméra
			dest.x = (s->getCoord()[0] - camPos[0]) * zoom;
			dest.y = (s->getCoord()[1] - camPos[1]) * zoom;

			dest.w = s->getLargeur() * zoom;
			dest.h = s->getHauteur() * zoom;

			std::cout << "coordonnées récupérées" << std::endl;

			//SDL_QueryTexture(s.textures[0], NULL, NULL, &dest.w, &dest.h);
			SDL_RenderCopy(renderer, s->getRightTexture(), NULL, &dest);
		}
		else{
			//Enlever de la liste 
		}
		std::cout << "fin affichage " << s->name << std::endl;
	}
	SDL_RenderPresent(renderer); // Met à jour l'écran avec le backbuffer du renderer
};