#include "Venera.hpp"

int main(){
    Venera venera = Venera();
    App app();

    app.window = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_RESIZABLE);

    affichage aff(app.renderer);

    while(1){
        
        venera.waitquit();

        aff.affiche_all();

        SDL_Delay(16);
    }
}
