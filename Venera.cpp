#include "Venera.hpp"

Venera::Venera() {
	app = new App();
	app->window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_RESIZABLE); // Création de la fenêtre
	app->renderer = SDL_CreateRenderer(app->window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// selon https://fr.wikibooks.org/wiki/Programmation_avec_la_SDL/Le_renderer on peut donner un flag à SDL_CreateRenderer :
	// SDL_RENDERER_ACCELERATED	Utilise l'accélération matérielle, c'est à dire la carte graphique. Il est fortement recommandé de le mettre puisque c'est un des atouts majeurs de la SDL 2.0 par rapport à la SDL 1.2 et surtout parce que c'est beaucoup plus rapide.
	// SDL_RENDERER_PRESENTVSYNC	Synchronise le rendu avec la fréquence de rafraîchissement. La fréquence de rafraîchissement correspond au nombre de fois où l'écran est mis à jour par seconde. Ainsi, le rendu sera synchronisé avec celle-ci.

	if(app->renderer == NULL) { //gestion des erreurs
		std::cout << "Erreur lors de la creation d'un renderer : " << SDL_GetError() << std::endl;;
	}
	else {
		stockeur = new Stockeur();
		Sprite::stockeur = stockeur;
		afficheur = new Affichage(app->renderer, stockeur);
		Sprite::afficheur = afficheur;
		Sprite::map = new Map();

		mc = new Mc();
		j2 = new Joueur2();
		stockeur->addMc(mc);
		stockeur->addJoueur2(j2);
		afficheur->setPlayer(mc);
		
		input = new Input();

		initialisation();
	}
}


void Venera::initialisation() {
	//enemies.push_back(new BasicSkeleton(100, 100));
	spawnPoints.push_back(new SpawnPoint(50, 50, this));
	

	// ça c'est juste un exemple de bordure de map pour voir si ça marche un peu
	uint8_t liste[MAX_FPE] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	std::cout << "création de la bordure" << std::endl;
	Entite* bord0 = new Entite("Bord0", 1, liste);
	bord0->setLargeur(600);
	bord0->setHauteur(50);
	bord0->setCoord(300, -25, 0);
	bord0->setOnScreen(true);
	bord0->autoSetHitBox();
	stockeur->addRectEntite(bord0);

	/*
	Entite* bord1 = new Entite("Bord1", 1, liste);
	bord1->setLargeur(50);
	bord1->setHauteur(600);
	bord1->setCoord(625, 300, 0);
	bord1->setOnScreen(true);
	bord1->autoSetHitBox();
	stockeur->addRectEntite(bord1);
*/

	Entite* bord2 = new Entite("Bord2", 1, liste);
	bord2->setLargeur(600);
	bord2->setHauteur(50);
	bord2->setCoord(300, 625, 0);
	bord2->setOnScreen(true);
	bord2->autoSetHitBox();
	stockeur->addRectEntite(bord2);

	Entite* bord3 = new Entite("Bord3", 1, liste);
	bord3->setLargeur(50);
	bord3->setHauteur(600);
	bord3->setCoord(-25, 300, 0);
	bord3->setOnScreen(true);
	bord3->autoSetHitBox();
	stockeur->addRectEntite(bord3);
}

void Venera::update() {
	// Ce que cette fonction doit faire :
	// update des enemies pour qu'ils prennent des décisions (dont celles de se déplacer)
	// update des Entite pour les déplacer
	// update des Sprites pour les faire changer d'apparence
	// récupére la touche pressée par le joueur
	input->update();
	mc->update(); 
	j2->update();

	for (Enemies* enemy : *(stockeur->getEnemiesVector())) {
		// if(enemy->contact(mc)){
		// 	//std::cout << "L'ennemi touche le mc" << std::endl;
		// 	enemy->attackBehaviour();
		// }
		
		// if(mc->getAttack()->getOnScreen()){
		// 	if(enemy->contact(mc->getAttack())){
		// 		//std::cout << "L'attaque touche l'ennemi" << std::endl;
		// 		enemy->takingDamage(mc->getAttack());
		// 	}
		// }
		enemy->update();
	}

	for (Sprite* s : *(stockeur->getSpriteVector())) {
		s->update();
	}


	for (SpawnPoint* sp : spawnPoints) {
		sp->update();
	}

	afficheur->update();
}

int main(){
	std::cout << "main start" << std::endl;
	Venera venera;

	Uint32 FrameStartTimeMs;
	Uint32 FrameEndTimeMs;
	Uint32 FrameNormalTimeMs = 1000/FPS;
	long FrameTimeMS;
	long moyenne = 0;
	Uint8 echantillon = 15;
	Uint8 compteur = echantillon;
	
	// uint8_t i=5;
	while(true){
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
			std::cout << "FPS : " << moyenne << std::endl;
			moyenne = 0;
			compteur = echantillon;
		}
	}
}
