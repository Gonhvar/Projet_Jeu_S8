#include "affichage.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */

Affichage::Affichage(SDL_Renderer* rend, Stockeur* st) : renderer(rend) {
	camPos[0] = 0;
	camPos[1] = 0;
	zoom = 1;

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

void Affichage::setZoom(float z) {
	zoom = z;
}

void Affichage::setCamPos(float x, float y) {
	camPos[0] = x;
	camPos[1] = y;
}

void Affichage::setPlayer(Mc* thePlayer) {
	player = thePlayer;
}

void Affichage::visit(Sprite* s, const std::string spriteName) {
	// Ajoute s dans sprites et va chercher ses textures

	// On vérifie si l'image n'a pas déjà été chargée
	imIterator = imageChargees.find(spriteName);
	if (imIterator != imageChargees.end()) { // Déjà chargée
		s->setTexture(imIterator->second);
		std::cout << "Image de " << spriteName << " déjà chargée :)" << std::endl;
	}
	else { // Sinon on la charge et on la stocke dans imageChargees
		std::string pathComplet = PATH_TO_TEXTURE_FOLDER + spriteName + "/" + spriteName + "_Sheet" + imageFormat;
		std::cout << "Chargement de " << spriteName << " à " << pathComplet << std::endl;
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

void Affichage::enleveSprite(const Sprite& s) {
	//remove(sprites.begin(), sprites.end(), &s);
}

void Affichage::update(){
	//if (!player->dashOn) SDL_RenderClear(renderer);
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
	for(Sprite* s : *sprites){
		if(s->getOnScreen()){
			// position relative du Sprite par rapport à la caméra
			dest.x = (s->getSpriteX() - camPos[0]) * zoom;
			dest.y = (s->getSpriteY() - camPos[1]) * zoom;

			dest.w = s->getLargeur() * zoom;
			dest.h = s->getHauteur() * zoom;

			//SDL_QueryTexture(s.textures[0], NULL, NULL, &dest.w, &dest.h);
			//SDL_RenderCopy(renderer, s->getRightTexture(), NULL, &dest);
			SDL_RenderCopyEx(renderer, s->getTexture(), s->getRightRectangle(), &dest, 0, NULL, s->getFlip() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		}
	}
	SDL_RenderPresent(renderer); // Met à jour l'écran avec le backbuffer du renderer
};
