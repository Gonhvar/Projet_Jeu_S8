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
        // std::cout << "rate : " << rate << std::endl;
        rate +=t;
        if(random <= rate){
            item = items[i];
            // std::cout << "Item : " << item << std::endl;
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
    std::vector<std::string> noms = {
        "Bonus_degats",
        "Bonus_dash",
        "Bonus_mouvement"
    };

    States* newStates;
    for (uint8_t i=0; i<noms.size(); i++) {
        newStates = new States();
        newStates->spriteName = noms[i]; 
        newStates->nbEtats = 1;
        newStates->nbFrameParEtat[0] = 1;
        for (int j=1; j<newStates->nbEtats; j++) {
            newStates->nbFrameParEtat[j] = 0;
        }
        vect->push_back(newStates);
    }

    Drop::etatsDrop = vect;
}


void Drop::update(){
    // std::cout << "Update Item : " << _coord[1] << std::endl;

    //Si il est récupéré 
    if(stillInUse){
        // std::cout << "Cd : " << a << std::endl;
        if( SDL_GetTicks()-startUse > cd){
            std::cout << "Auto-Destruction Item" << std::endl;
            switch(item){
                case 1 :
                    stockeur->getMc()->getAttacks()->setAttackMultiplier(1);
                    break;
                
                case 2 :
                    otherEntite->getDepForce() /= 1.5;
                    break;

                case 3 :
                    stockeur->getMc()->getDashValue() = 1;
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
    }
    else{
        addForce(0, sin( 0.1 * SDL_GetTicks()) * 64);
    }
}


//Charger ici les textures en fonction de l'item qui spawn
void Drop::selectItem(){
    switch(item){
        case 0 : 
            //Pas d'item
            std::cout << "Creation 0" << std::endl;
            states = (*Drop::etatsDrop)[0];
            markedForDeath = true;
            break;
        
        case 1 : 
            //Dégats
            std::cout << "Creation 1" << std::endl;
            states = (*Drop::etatsDrop)[0];
            break;
        case 2 :
            //Vitesse
            std::cout << "Creation 2" << std::endl;
            states = (*Drop::etatsDrop)[1];
            break;
        
        case 3 :
            //Dash
            std::cout << "Creation 3" << std::endl;
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
                //Dégats
                stockeur->getMc()->getAttacks()->setAttackMultiplier(2);
                cd = 10000;
                break;
            case 2 : 
                //Vitesse 
                other->getDepForce() *= 2;
                cd = 5000;
                break;

            case 3 :
                //Dash 
                stockeur->getMc()->getDashValue() = 2;
                cd = 15000;
                break;

            default :
                markedForDeath = true;
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

        case 2 :
            stockeur->getMc()->getColor() = BLUE;
            break;

        case 3 :
            stockeur->getMc()->getColor() = GREEN;
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