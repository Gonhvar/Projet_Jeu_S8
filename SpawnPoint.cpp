#include "SpawnPoint.hpp"

const States* SpawnPoint::etatsSpawnPoint;

/* CONSTRUCTEURS ET DESTRUCTEURS */
SpawnPoint::SpawnPoint(){
    states = SpawnPoint::etatsSpawnPoint;

    stockeur->addSpawn(this);
};

SpawnPoint::SpawnPoint(float x, float y, int wave) {
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
        
		this->wave = wave;
        onScreen = true;  
		std::cout << "Création de SpawnPoint : " << states->spriteName << std::endl;


    stockeur->addSpawn(this);
}

SpawnPoint::~SpawnPoint() {
    stockeur->removeSpawn(this);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void SpawnPoint::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "SpawnPoint"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
    newStates->nbEtats = 1;
    newStates->nbFrameParEtat[0] = 1;
    for (int i=1; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	SpawnPoint::etatsSpawnPoint = newStates;
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

                case 1 :
                    //SkeletonShooter
                    new SkeletonShooter(_coord[0], _coord[1]);
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
                    spawn(1, 0, 1000.0);
                    break;
                case 1 :
                    //Rien pour l'instant mais à remplir pour faire le jeu
                    break;
                
                default :
                    phase = 0;
                    break;
            }
            

            break;

        case 1 :
            switch(phase){
                case 0 : 
                    //std::cout << "Phase 0" << std::endl;
                    spawn(1, 1, 500.0);
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
    spawnWave(wave);
}





// Fonctions de sauvegarde de l'objet
std::string SpawnPoint::serialize(std::string& toWrite) {
	Entite::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << i << "|" << phase << "|" << wave << "|" << FrameStartTimeMs << "|" ;
    toWrite += oss.str();
    return "SpawnPoint";
}

std::istringstream& SpawnPoint::deSerialize(std::istringstream& iss) {
    Entite::deSerialize(iss);
    std::string token;
    if (std::getline(iss, token, '|')) {
        i = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        phase = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        wave = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        FrameStartTimeMs = std::stoul(token);
    }
	return iss;
}