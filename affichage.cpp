#include "affichage.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Affichage::Affichage(){};

Affichage::Affichage(SDL_Renderer* rend) : renderer(rend) {
	camPos[0] = 0;
	camPos[1] = 0;
	zoom = 1;

	Sprite::afficheur = this;

	noTexture = IMG_LoadTexture(renderer, NO_TEXTURE_FOUND);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Affichage::setZoom(float z) {
	zoom = z;
}

void Affichage::setCamPos(float x, float y) {
	camPos[0] = x;
	camPos[1] = y;
}

void Affichage::visit(Sprite* s, std::string& spriteName, uint8_t nbEtats, std::vector<uint8_t>& nbFrameParEtat) {
	// Ajoute s dans sprites et va chercher ses textures

	// On vérifie si l'image n'a pas déjà été chargée
	imIterator = imageChargees.find(spriteName);
	if (imIterator != imageChargees.end()) { // Déjà chargée
		s->getTexture() = imIterator->second;
	}
	else { // Sinon on la charge et on la stocke dans imageChargees
		SDL_Texture* textureChargee;
		TexturePack* newTexture = new TexturePack(nbEtats);
		for (int etat=0; etat<nbEtats; etat++) {
			(*newTexture)[etat].resize(nbFrameParEtat[etat]);
			for (int frame=0; frame<nbFrameParEtat[etat]; frame++) {
				std::string pathComplet = PATH_TO_TEXTURE_FOLDER + spriteName + std::to_string(etat) + "/" + std::to_string(frame) + imageFormat;
				const char* filename = pathComplet.c_str();
				
				textureChargee = IMG_LoadTexture(renderer, filename);
				if (!textureChargee) { // L'image n'a pas pu être chargée. On prend la texture par défaut.
					std::cout << "Erreur de chargement de " << spriteName << " ---> a ete cherche a : " << pathComplet << std::endl;
					textureChargee = noTexture;
				}
				(*newTexture)[etat][frame] = textureChargee;
			}
		}
		s->getTexture() = newTexture;
		
		imageChargees[spriteName] = textureChargee;
	}

	sprites.push_back(s);
};

void Affichage::enleveSprite(const Sprite& s) {
	//remove(sprites.begin(), sprites.end(), &s);
}

void Affichage::update(){
	enemiesUpdate();
	affiche_all();
}

void Affichage::enemiesUpdate(){
	for(stt s : sprites){
		//On regarde si le sprite est un enemie (Soit ça, soit on stock les enemies dans un tableau ?)
		if(dynamic_cast<Enemies*>(s.sprite) != nullptr){
			Enemies* en = dynamic_cast<Enemies*>(s.sprite);
			en->deplacementBehaviour();
			en->attackBehaviour();
			
		}
		
	}
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

			//SDL_QueryTexture(s.textures[0], NULL, NULL, &dest.w, &dest.h);
			SDL_RenderCopy(renderer, s.textures[0], NULL, &dest);
		}
		else{
			//Enlever de la liste 
		}
	}
	SDL_RenderPresent(renderer); // Met à jour l'écran avec le backbuffer du renderer
};