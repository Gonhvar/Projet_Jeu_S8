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
	}
}

void Venera::keyboard_event(){

}

int main(){
	Venera venera;
	std::string mc_name = "robot";

	Mc p1(mc_name,*venera.afficheur);

	// s1.setOnScreen(true);
	// s1.setCoord(200, 200, 0);
	// s1.setLargeur(100);
	// s1.setHauteur(100);
	//venera.waitquit();

	while(1){
		
		p1.get_keypress();
		venera.afficheur->affiche_all();
		SDL_Delay(20);
	}

}
