#include "SpawnPoint.hpp"

SpawnPoint::SpawnPoint(){};

SpawnPoint::SpawnPoint(float x, float y) {
    _coord[0] = x;
    _coord[1] = y;
    i = 0;
    phase = 0;
    FrameStartTimeMs = SDL_GetTicks();

    //states = &(etatsDesSpawnPoint);
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "SpawnPoint"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}
		states = newStates;    
		std::cout << "Création de SpawnPoint : " << states->spriteName << std::endl;
}

void SpawnPoint::spawn(int number, int select, float timing){
    //timing -> 1000 = 1 seconde
    if(i < number){
        if(SDL_GetTicks()-FrameStartTimeMs > timing){
            switch(select){
                case 0 :
                    //BasicSkeleton 
                    new BasicSkeleton(_coord[0], _coord[1]); // push automatiquement l'Enemy dans les listes :
                                            // sprites
                                            // circEntities
                                            // enemies
                    break;

                default :
                    break;
            }
            i++;
            FrameStartTimeMs = SDL_GetTicks();
        }
    }
    else{
        i=0;
        phase++;
    }
}

void SpawnPoint::spawnWave(int selectWave){
    //On peut designer les waves ici
    switch(selectWave){
        case 0 : 
            //std::cout << "Wave 0 avec " << phase <<std::endl;
            switch(phase){
                case 0 : 
                    //std::cout << "Phase 0" << std::endl;
                    spawn(20, 0, 1000.0);
                    break;
                case 1 :
                    //Rien pour l'instant mais à remplir pour faire le jeu
                    break;
                
                default :
                    phase = 0;
                    break;
            }
            

            break;

        default :
            break;
    }
}

void SpawnPoint::update(){
    //A modifier en fonction des besoins
    spawnWave(0);
}

