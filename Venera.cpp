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
		afficheur = new Affichage(app->renderer);
		Sprite::afficheur = afficheur;
	}

	initialisation();
}

void Venera::pushBackEnemies(Enemies* en){
		enemies.push_back(en);
}


void Venera::initialisation() {
	mc = new Mc();
	//enemies.push_back(new BasicSkeleton(100, 100));
	spawnpoints.push_back(new SpawnPoint(50, 50, this));
	
}

void Venera::update() {
	// On récupére la touche pressé par le joueur
	mc->update();
	
	for (Entite* sp : spawnpoints) {
		//test si c'est bien un spawnpoint (peut etre pas necessaire en fonction de la suite du code)
		if (dynamic_cast<SpawnPoint*>(sp) != nullptr)
		{
			//Le dynamic cast est obligé
			dynamic_cast<SpawnPoint*>(sp)->update();
		}
	}

	for (Enemies* enemy : enemies) {
		enemy->contact(mc);
		enemy->update();
	}

	for (Drop* droper : drop) {
		droper->update();
	}

	afficheur->update();
}

int main(){
	std::cout << "main start" << std::endl;
	Venera venera;
	//venera.initialisation();
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
