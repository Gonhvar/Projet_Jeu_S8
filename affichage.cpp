#include "affichage.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */

Affichage::Affichage(SDL_Renderer* rend, SDL_Window* win, Stockeur* st) : renderer(rend), window(win) {
	sprites = st->getSpriteVector();

	noTexture = IMG_LoadTexture(renderer, NO_TEXTURE_FOUND);
	if (!noTexture) { // L'image n'a pas pu être chargée. On prend la texture par défaut.
		std::cout << "Erreur de chargement de noTexture : ça sent pas bon là" << std::endl;
	}

	if ( TTF_Init() < 0 ) {
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	}else{
		//this opens a font style and sets a size
		font = TTF_OpenFont("Textures/Font/OpenSans-Regular.ttf", 20);
		if(!font){
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}

		//Blanc
		textColor = {255, 255, 255};
	}
}

Affichage::~Affichage(){
	TTF_CloseFont(font);
	TTF_Quit();
	for (auto& entry : imageChargees) {
		SDL_DestroyTexture(entry.second);
    }
    imageChargees.clear();
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Affichage::visit(Sprite* s, std::string className, const std::string spriteName) {
	// Ajoute s dans sprites et va chercher ses textures

	// On vérifie si l'image n'a pas déjà été chargée
	imIterator = imageChargees.find(spriteName);
	if (imIterator != imageChargees.end()) { // Déjà chargée
		s->setTexture(imIterator->second);
		// std::cout << "Image de " << spriteName << " déjà chargée :)" << std::endl;
	}
	else { // Sinon on la charge et on la stocke dans imageChargees
		std::string pathComplet = PATH_TO_TEXTURE_FOLDER + className + "/" + spriteName + "_Sheet" + imageFormat;
		// std::cout << "Chargement de " << spriteName << " à " << pathComplet << std::endl;
		const char* filename = pathComplet.c_str();
		SDL_Texture* textureChargee = IMG_LoadTexture(renderer, filename);
				
		if (!textureChargee) { // L'image n'a pas pu être chargée. On prend la texture par défaut.
			std::cout << "Erreur de chargement de " << spriteName << " ---> a ete cherche a : " << pathComplet << std::endl;
			textureChargee = noTexture;
		}
		s->setTexture(textureChargee);
		imageChargees[spriteName] = textureChargee;
	}
};

void Affichage::update(){
	Vector2D dep(0,0);
	if (Sprite::stockeur->getMc() != nullptr) {
		// Suivi du Mc et placement de la caméra
		SDL_GetWindowSize(window, windowSize, windowSize+1);
		camera.w = windowSize[0] / zoom;
		camera.h = windowSize[1] / zoom;

		dep.redef(
			Sprite::stockeur->getMc()->getX() - (camera.x + camera.w/2),
			Sprite::stockeur->getMc()->getY() - (camera.y + camera.h/2)
		);
		if (dep.norme > rayonDistMc) {
			dep.normeToV(dep.norme - rayonDistMc);
			camera.x += dep.x;
			camera.y += dep.y;
		}
	}
	SDL_RenderClear(renderer);

	affiche_all();
	
	if(Sprite::stockeur->getMc() != nullptr){
		afficheHealth();	
		//On change la couleur du mc 
		switch(Sprite::stockeur->getMc()->getColor()){
			case 1 :
				setMcColor(255, 0, 0);

				break;
			case 2 :
				setMcColor(0, 255, 0);
				break;

			case 3 :
				setMcColor(0, 0, 255);
				break;

			default :
				setMcColor(255, 255, 255);
				break;
		}
	}

	SDL_RenderPresent(renderer); // Met à jour l'écran avec le backbuffer du renderer
}


void Affichage::afficheHealth(){
	SDL_Rect dest;
	SDL_Surface* textSurface;
	SDL_Texture* text;

	//On va chercher les caractéristiques du joueur (jsp qui est le moins couteux entre ces deux méthodes)
	// char strtext[100];
	// sprintf(strtext, "PV : %d/%d", player->getPV(), player->getPVMax());

	std::string strtext = "PV : " + std::to_string(Sprite::stockeur->getMc()->getPV()) + "/" + std::to_string(Sprite::stockeur->getMc()->getPVMax());
	
	//std::cout << strtext << std::endl;
	
	textSurface = TTF_RenderText_Solid(font, strtext.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(renderer, textSurface);

	dest.x = 10;
	dest.y = 0;
	dest.w = textSurface->w;
	dest.h = textSurface->h;
	
	SDL_RenderCopy(renderer, text, NULL, &dest);

	SDL_DestroyTexture(text);
	SDL_FreeSurface(textSurface);
}

void Affichage::affiche_all() const{
	
	SDL_Rect dest;
	// On affiche la texture du sprite avec 
	for(Sprite* s : *sprites){
		if(s->getOnScreen()){
			// position relative du Sprite par rapport à la caméra
			float coefX = (s->getSpriteX() - camera.x) / camera.w + 1/2;
			float coefY = (s->getSpriteY() - camera.y) / camera.h + 1/2;

			dest.x = coefX * windowSize[0];
			dest.y = coefY * windowSize[1];
			dest.w = s->getLargeur() * zoom;
			dest.h = s->getHauteur() * zoom;

			//SDL_RenderCopy(renderer, s->getRightTexture(), NULL, &dest);
			SDL_RenderCopyEx(renderer, s->getTexture(), s->getRightRectangle(), &dest, 0, NULL, s->getFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		}
	}
};


void Affichage::setMcColor(Uint8 red, Uint8 green, Uint8 blue){
	// SDL_Texture* textureChargee = IMG_LoadTexture(renderer, pathComplet.c_str());
	SDL_SetTextureColorMod(Sprite::stockeur->getMc()->getTexture(), red, green, blue);
}	



int Affichage::getCameraX() {
	return camera.x;
}
int Affichage::getCameraY() {
	return camera.y;
}

float Affichage::getZoom() {
	return zoom;
}

void Affichage::zoomPlus() {
	zoom *= 1.1;
}
void Affichage::zoomMoins() {
	zoom /= 1.1;
}