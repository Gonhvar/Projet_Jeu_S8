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
	}
	initialisation();
}

void Venera::pushBackEnemies(Enemies* en){
		enemies.push_back(en);
}


void Venera::initialisation() {
	
	mc = new Mc();
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

	Entite* bord1 = new Entite("Bord1", 1, liste);
	bord1->setLargeur(50);
	bord1->setHauteur(600);
	bord1->setCoord(625, 300, 0);
	bord1->setOnScreen(true);
	bord1->autoSetHitBox();

	Entite* bord2 = new Entite("Bord2", 1, liste);
	bord2->setLargeur(600);
	bord2->setHauteur(50);
	bord2->setCoord(300, 625, 0);
	bord2->setOnScreen(true);
	bord2->autoSetHitBox();

	Entite* bord3 = new Entite("Bord3", 1, liste);
	bord3->setLargeur(50);
	bord3->setHauteur(600);
	bord3->setCoord(-25, 300, 0);
	bord3->setOnScreen(true);
	bord3->autoSetHitBox();
}

void Venera::update() {
	// On récupére la touche pressé par le joueur
	mc->update();

	for (SpawnPoint* sp : spawnPoints) {
		sp->update(); // Appel le update de Entite pas de SpawnPoint
						// Il vaut mieux avoir une liste de spawnPoint
						// OU update() devient un attribut de type pointeur de fonction
						// On peut alors donner à chaque Entite une fonction update ou il se static_cast correctement dedans;

	}

	for (Enemies* enemy : enemies) {

		if(enemy->contact(mc)){
			//std::cout << "L'ennemi touche le mc" << std::endl;
			enemy->attackBehaviour();
		}
		
		if(mc->getAttack()->getOnScreen()){
			if(enemy->contact(mc->getAttack())){
				//std::cout << "L'attaque touche l'ennemi" << std::endl;
				enemy->takingDamage(mc->getAttack());
			}
		}
		enemy->update();
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
			//std::cout << "FPS : " << moyenne << std::endl;
			moyenne = 0;
			compteur = echantillon;
		}
	}
}
