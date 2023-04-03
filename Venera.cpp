#include "Venera.hpp"

int main(){
    Venera venera = Venera();

    SDL_CreateWindow("Jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_RESIZABLE);

    while(1){
        venera.waitquit();
        SDL_Delay(16);
    }
}
