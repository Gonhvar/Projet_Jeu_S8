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
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Affichage::setZoom(float z) {
	zoom = z;
}

void Affichage::setCamPos(float x, float y) {
	camPos[0] = x;
	camPos[1] = y;
}

void Affichage::visit(Sprite* s, const States* states) {
	// Ajoute s dans sprites et va chercher ses textures

	// On vérifie si l'image n'a pas déjà été chargée
	imIterator = imageChargees.find(states->spriteName);
	if (imIterator != imageChargees.end()) { // Déjà chargée
		s->setTexture(imIterator->second);
		//std::cout << "Image de " << states->spriteName << " déjà chargée :)" << std::endl;
	}
	else { // Sinon on la charge et on la stocke dans imageChargees
		SDL_Texture* textureChargee;
		TexturePack* newTexture = new TexturePack(states->nbEtats);
		for (int etat=0; etat<states->nbEtats; etat++) {
			(*newTexture)[etat].resize(states->nbFrameParEtat[etat]);
			for (int frame=0; frame<states->nbFrameParEtat[etat]; frame++) {
				std::string pathComplet = PATH_TO_TEXTURE_FOLDER + states->spriteName + "/" + std::to_string(etat) + "/" + std::to_string(frame) + imageFormat;
				std::cout << "Loading : " << pathComplet << std::endl;
				
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

		//On stock le pointeur vers le joueur
		if(s->getName() == "Robot"){
			player = dynamic_cast<Mc*>(s);
		}
	}

	sprites.push_back(s);
};

void Affichage::enleveSprite(const Sprite& s) {
	//remove(sprites.begin(), sprites.end(), &s);
}

void Affichage::update(){
	SDL_RenderClear(renderer);
	afficheHealth();
	affiche_all();
}

//Cette fonction ne marche pas encore 
void Affichage::afficheHealth(){
	SDL_Rect dest;
	SDL_Surface* textSurface;
	SDL_Texture* text;

	//On va chercher les caractéristiques du joueur (jsp qui est le moins couteux entre ces deux méthodes)
	// char strtext[100];
	// sprintf(strtext, "PV : %d/%d", player->getPV(), player->getPVMax());

	std::string strtext = "PV : " + std::to_string(player->getPV()) + "/" + std::to_string(player->getPVMax());
	
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
	for(Sprite* s : sprites){
		// std::cout << "affichage de : " << s << " dont le nom est : " << s->getStates()->spriteName << std::endl;
		if(s->getOnScreen()){
			// position relative du Sprite par rapport à la caméra
			dest.x = (s->getCoord()[0] - camPos[0]) * zoom;
			dest.y = (s->getCoord()[1] - camPos[1]) * zoom;

			dest.w = s->getLargeur() * zoom;
			dest.h = s->getHauteur() * zoom;

			// std::cout << "coordonnées récupérées" << std::endl;

			//SDL_QueryTexture(s.textures[0], NULL, NULL, &dest.w, &dest.h);
			SDL_RenderCopy(renderer, s->getRightTexture(), NULL, &dest);
		}
		else{
			//Enlever de la liste 
		}
		// std::cout << "fin affichage " << s->name << std::endl;
	}
	SDL_RenderPresent(renderer); // Met à jour l'écran avec le backbuffer du renderer
};