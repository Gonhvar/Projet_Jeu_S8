#include "Venera.hpp"

Venera::Venera() {
	window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_RESIZABLE); // Création de la fenêtre
	renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// Hide the mouse cursor
    SDL_ShowCursor(SDL_DISABLE);

	// selon https://fr.wikibooks.org/wiki/Programmation_avec_la_SDL/Le_renderer on peut donner un flag à SDL_CreateRenderer :
	// SDL_RENDERER_ACCELERATED	Utilise l'accélération matérielle, c'est à dire la carte graphique. Il est fortement recommandé de le mettre puisque c'est un des atouts majeurs de la SDL 2.0 par rapport à la SDL 1.2 et surtout parce que c'est beaucoup plus rapide.
	// SDL_RENDERER_PRESENTVSYNC	Synchronise le rendu avec la fréquence de rafraîchissement. La fréquence de rafraîchissement correspond au nombre de fois où l'écran est mis à jour par seconde. Ainsi, le rendu sera synchronisé avec celle-ci.

	if(renderer == NULL) { //gestion des erreurs
		std::cout << "Erreur lors de la creation d'un renderer : " << SDL_GetError() << std::endl;;
	}
	else {
		stockeur = new Stockeur();
		stockeur->removeSprites(nullptr);
		Sprite::stockeur = stockeur;
		stockeur->setMode(MODE_JEU);

		afficheur = new Affichage(renderer, window, stockeur);
		Sprite::afficheur = afficheur;
		
		Sprite::map = new Map();

		stockeur->addMc(new Mc());

		stockeur->addJoueur2(new Joueur2());
		
		input = new Input();
		input->addMe(Sprite::stockeur->getMc());

		audioM = new AudioManager();
		stockeur->addAudioManager(audioM);

		initialisation();
	}
}


void Venera::initialisation() {
	// enemies.push_back(new BasicSkeleton(100, 100));
	// spawnPoints.push_back(new SpawnPoint(50, 50, 0));
	spawnPoints.push_back(new SpawnPoint(50, 50, 1));
	

	// ça c'est juste un exemple de bordure de map pour voir si ça marche un peu
	uint8_t liste[MAX_FPE] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	std::cout << "création de la bordure" << std::endl;
	Entite* bord0 = new Entite("Bord0", 1, liste);
	bord0->setLargeur(600);
	bord0->setHauteur(50);
	bord0->setCoord(300, -25, 0);
	bord0->setOnScreen(true);
	bord0->autoSetHitBox();
	bord0->hitBoxType(0, 1);

	Entite* bord1 = new Entite("Bord1", 1, liste);
	bord1->setLargeur(50);
	bord1->setHauteur(600);
	bord1->setCoord(625, 300, 0);
	bord1->setOnScreen(true);
	bord1->autoSetHitBox();
	bord1->hitBoxType(0, 1);


	Entite* bord2 = new Entite("Bord2", 1, liste);
	bord2->setLargeur(600);
	bord2->setHauteur(50);
	bord2->setCoord(300, 625, 0);
	bord2->setOnScreen(true);
	bord2->autoSetHitBox();
	bord2->hitBoxType(0, 1);

	Entite* bord3 = new Entite("Bord3", 1, liste);
	bord3->setLargeur(50);
	bord3->setHauteur(600);
	bord3->setCoord(-25, 300, 0);
	bord3->setOnScreen(true);
	bord3->autoSetHitBox();
	bord3->hitBoxType(0, 1);

	//A REMETTRE A LA FIN POUR AVOIR LA MUSIQUE 
	// stockeur->getAudioManager()->playMusic("Music_01");
}

void Venera::update() {
	// Ce que cette fonction doit faire :
	// update des enemies pour qu'ils prennent des décisions (dont celles de se déplacer)
	// update des Entite pour les déplacer
	// update des Sprites pour les faire changer d'apparence
	// récupére la touche pressée par le joueur

	// Le joueur prend une décision (appui d'une touche)
	input->update();

	if (Sprite::stockeur->getMenuOff()) { // Pas le menu
		std::vector<Sprite*>& spriteListe = *(stockeur->getSpriteVector());
		switch (Sprite::stockeur->getMode()) {

			
			case MODE_JEU :
				//On arrete les enemy et les sprites car ils utilisent la position du joueur 
				//Solution possible : Mettre une variable dans stockeur de la position du MC qu'on mettrait à jour 
				if(Sprite::stockeur->getMc() != nullptr){
					
					Sprite::stockeur->getMc()->update();
					Sprite::stockeur->getJ2()->update();

					// Les Enemies prennent leur décisions
					for (Enemies* enemy : *(stockeur->getEnemiesVector())) {
						enemy->update();
					}

					// Frottements, collisions et déplacement des CircEntite
					std::vector<Entite*>& liste = *(stockeur->getCircEntiteVector());
					for (unsigned int i=0; i<liste.size(); i++) {
						liste[i]->updateSpeedWithRectCollisions();
						for (unsigned int j=i+1; j<liste.size(); j++) {
							liste[i]->moveCollisionCercle2(liste[j]);
						}
						liste[i]->autoTranslate();
					}

					// Les SpawnPoints font spawner
					for (SpawnPoint* sp : spawnPoints) {
						sp->update();
					}

					for(Drop* d : *(stockeur->getItemVector())){
						d->update();
					}
				}

				// Les Sprite sont mis à jour ou supprimés selon
				for (unsigned int s=0; s < spriteListe.size(); s++) {
					if (stockeur->printEverything) {
						std::cout << "eval " << s << " : " << spriteListe[s] << " ";
					}
					if (spriteListe[s]->markedForDeath) {
					// if (true) {
						if (stockeur->printEverything) {
							std::cout << "Marked (" << spriteListe[s]->getStates()->spriteName << ")" << std::endl;
						}
						delete(spriteListe[s]);
						s--;
					}
					else {
						if (stockeur->printEverything){
							std::cout << "Not Marked (" << spriteListe[s]->getStates()->spriteName << ")" << std::endl;
						}
						spriteListe[s]->update();
					}
				}

				stockeur->getGameTime() = SDL_GetTicks();
				
				break;

			case MODE_MAP :
				std::cout << "Mode Map" <<	std::endl;
				break;
			default : 
				std::cout << "Mode noMode :(" <<	std::endl;
				break; 
		}
	}
	else { // Mode menu
		
	}
	// Le reste est affiché
	afficheur->update();
}

int main(){
	std::cout << "main start" << std::endl;
	Venera venera;

	Uint32 FrameStartTimeMs;
	Uint32 FrameEndTimeMs;
	Uint32 FrameNormalTimeMs = 1000/FPS;
	// FrameNormalTimeMs = 400;
	long FrameTimeMS;
	long moyenne = 0;
	Uint8 echantillon = 15;
	Uint8 compteur = echantillon;
	
	while(true){
	    // if (Sprite::stockeur->printEverything) std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;



		//On récupére le temps actuel
		FrameStartTimeMs = SDL_GetTicks();

		//Update
		venera.update();

		FrameEndTimeMs = SDL_GetTicks();

		//On attends le temps requis pour avoir un nombre de FPS
		while(SDL_GetTicks() - FrameStartTimeMs < FrameNormalTimeMs);
		//Calcul des FPS
		FrameTimeMS = FrameEndTimeMs - FrameStartTimeMs;
		FrameTimeMS = 1000 / (float) FrameTimeMS;
		moyenne += FrameTimeMS;
		if (!compteur--) {
			moyenne /= echantillon;
			// std::cout << "FPS : " << moyenne << std::endl;
			moyenne = 0;
			compteur = echantillon;
		}
	}

	Mix_Quit();
	SDL_Quit();

	// delete Sprite::stockeur->getMc();
	// std::cout << "DELETED MC : " << Sprite::stockeur->getMc() << std::endl;
	// Mc* mc = new Mc();
	// Sprite::stockeur->addMc(mc);
	// std::cout << "REMADE MC : " << Sprite::stockeur->getMc() << std::endl;
	// std::cout << Sprite::stockeur->getMc()->getAttacks() << std::endl;
	// Sprite::stockeur->getMc()->getAttacks()->update(2, 0, 0, 0);

	// std::fstream file("data.txt", std::ios::out | std::ios::trunc);

    // if (file.is_open()) {
    //     std::string myString = "";
	// 	Vector2D v(1, 2);
	// 	v.serialize(myString);
	// 	file << myString;
    //     file.close();
    //     std::cout << "Enregistrement terminé." << std::endl;
    // } else {
    //     std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    // }

	// std::ifstream inputFile("data.txt"); 
	
    // if (inputFile.is_open()) {
    //     std::string content((std::istreambuf_iterator<char>(inputFile)),
    //                         (std::istreambuf_iterator<char>()));
        
    //     std::cout << "Contenu du fichier :\n" << content << std::endl;
	// 	Vector2D v(0, 0);
	// 	v.deSerialize(content);
    //     inputFile.close();
    // } else {
    //     std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    // }

	// std::string writing = "";
	// std::cout << "Mc : " << Sprite::stockeur->getMc()->serialize(writing) << std::endl;;
	// std::cout << "a ecrit :" << writing;

	// Sprite::stockeur->getMc()->setCoord(0, 1, 2);
	// Sprite::stockeur->getMc()->deSerialize(writing);
	// std::cout << "a lu : " << Sprite::stockeur->getMc()->getX() << ", " << Sprite::stockeur->getMc()->getY() << ", " << Sprite::stockeur->getMc()->getCoord()[2] << std::endl;
}
