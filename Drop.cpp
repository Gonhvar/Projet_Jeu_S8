#include "Drop.hpp"
#include "Mc.hpp"


const std::vector<States*>* Drop::etatsDrop;

/* CONSTRUCTEURS ET DESTRUCTEURS */
Drop::Drop() {
    states = (*Drop::etatsDrop)[0];
    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;

    stateRect.w = 16;
    stateRect.h = 16;
    hitBoxType(1, 0);
    stockeur->addItem(this);
    
    onScreen = true;
    addSprite("Drop");
}


Drop::Drop(std::vector<int> items, std::vector<int> taux, int x, int y) {
    faction = MC_FRIENDLY_FACTION;

    std::srand(time(NULL));
    int random = 1 + (rand()%100);
    int rate = 0;
    
    masse = 100;
    frottements = 100;
    rayon = 24;

    _coord[0] = x;
    _coord[1] = y -10;

    _largeur = 32;
    _hauteur = 32;
    autoSetHitBox();
    hitBoxType(1, 0);

    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;

    stateRect.w = 16;
    stateRect.h = 16;

    // std::cout << "Random : " << random << std::endl; 
    int i = 0;
    for(int t : taux){
        rate +=t;
        // std::cout << "rate : " << rate << std::endl;
        if(random <= rate){
            item = items[i];
            break;
        }
        i++;
    }

    selectItem();
    stockeur->addItem(this);

    stillInUse = false;
    onScreen = true;
    addSprite("Drop");
}

Drop::~Drop() {
	std::cout << "Delete Drop" << std::endl;
    stockeur->removeItem(this);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Drop::initialisation() {
    std::vector<States*>* vect = new std::vector<States*>();
    vect->resize(0);
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "Bonus_degats"; 
    newStates->nbEtats = 1;
    newStates->nbFrameParEtat[0] = 1;
    for (int i=1; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	vect->push_back(newStates);
    Drop::etatsDrop = vect;
}


void Drop::update(){
    // std::cout << "Update Item : " << _coord[1] << std::endl;

    //Detection de prise du joueur à rajouter

    //Si il est récupéré 
    if(stillInUse){
        // std::cout << "Cd : " << a << std::endl;
        if( SDL_GetTicks()-startUse > cd){
            std::cout << "Auto-Destruction Item" << std::endl;
            switch(item){
                case 1 :
                    otherEntite->getDepForce() /= 1.5;
                    break;
                
                default :
                    break;
            }
            stockeur->getMc()->getColor() = NONE;
            markedForDeath = true;
        }
        else{
            //Si le joueur est toujours sous l'effet de l'effet, il reset la couleur du joueur
            resetColor();
        }
    }else{
        addForce(0, sin( 0.1 * SDL_GetTicks()) * 64);
    }
}


//Charger ici les textures en fonction de l'item qui spawn
void Drop::selectItem(){
    item = !item ? 1 : item;
    switch(item){
        case 0 : 
            //Pas d'item
            // std::cout << "Creation 0" << std::endl;
            markedForDeath = true;
            break;
        
        case 1 : 
            states = (*Drop::etatsDrop)[0];
            break;

        default :
            break;
    }

    stockeur->getMc()->getColor() = NONE;
}

void Drop::reactionContact(Entite* other) {
    
    otherEntite = other;

    if (other->getFaction() == MC_FACTION) {
        std::cout << "Ramassé" << std::endl;
        switch(item){
            case 1 : 
                other->getDepForce() *= 1.5;
                cd = 1000;
                break;

            default :
                break;
        }

        //Il faut une autre solution car c'est pas possible ça
        _coord[0] = -999;
        _coord[1] = -999;

        startUse = SDL_GetTicks();
        onScreen = false;
        stillInUse = true;
    }
}

//Mettre les couleurs ici :
void Drop::resetColor(){
    switch(item){
        case 1 : 
                stockeur->getMc()->getColor() = RED;
                break;

        default :
                break;
    }
}





// Fonctions de sauvegarde de l'objet
std::string Drop::serialize(std::string& toWrite) {
	Entite::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << item << "|" << stillInUse << "|" << cd << "|" << startUse << "|";
    toWrite += oss.str();
    return "Drop";
}

std::istringstream& Drop::deSerialize(std::istringstream& iss) {
    Entite::deSerialize(iss);
    std::string token;
    if (std::getline(iss, token, '|')) {
        item = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        stillInUse = readBool(token);
    }
    if (std::getline(iss, token, '|')) {
        cd = std::stoul(token);
    }
    if (std::getline(iss, token, '|')) {
        startUse = std::stoul(token);
    }
	return iss;
}