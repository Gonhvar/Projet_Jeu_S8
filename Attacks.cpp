#include "Attacks.hpp"


const States* Attacks::etatsAttacks;

Attacks::Attacks(){
    std::cout << "new Attacks" << std::endl;
    faction = MC_FACTION;
    
    _hauteur = 64;
    _largeur = 64;
    autoSetHitBox();
    hitBoxType(1, 0);

	directionX = 0;
    directionY = 0;

    depForce = BASICSPEED;

    rayon = 30;
    masse = 100;


    setCoord(0,0,0);
    setOnScreen(false);

    // Pas encore de SpriteSheet pour Attack : retour au 32x32 de noTexture
    // stateRect.w = 32;
    // stateRect.h = 32;

    states = Attacks::etatsAttacks;
    addSprite("Attacks");

    state = 0;
    attackMultiplier = 1;
    startCdAttack = SDL_GetTicks();
    needToClearCombo = false;
}

void Attacks::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "Attacks"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
    newStates->nbEtats = 1;
    newStates->nbFrameParEtat[0] = 1;
    for (int i=1; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	Attacks::etatsAttacks = newStates;
}

void Attacks::updateDirection(int pushForceH, int pushForceB, int pushForceG, int pushForceD){
    this->pushForceH = pushForceH;
    this->pushForceB = pushForceB;
    this->pushForceG = pushForceG;
    this->pushForceD = pushForceD;
}

void Attacks::update(){
    if (Sprite::stockeur->printEverything) {
        std::cout << "Attacks::update()" << std::endl;
    }

    if(stockeur->getGameTime()-startCdAttack > cdAttack){
        state = 0;
        this->setOnScreen(false);
        if(needToClearCombo){
            std::cout << "Combo cleared" << std::endl; 
            combo.clear();
            needToClearCombo = false;
        }
        _coord[0] = playerCoord[0];
        _coord[1] = playerCoord[1]; 
    }
    else{
        Vector2D v(directionX, directionY);
        move(v);
        addForce(v);
    }
    
    updatePlayerCoord();

    if(state != 0){
        //Met à jour l'attaque
        updateHitBox(range*directionX, range*directionY);
    }


}

void Attacks::updatePlayerCoord(){
    playerCoord[0] = stockeur->getMc()->getX();
    playerCoord[1] = stockeur->getMc()->getY();
}

void Attacks::updateHitBox(float attackRangeX, float attackRangeY){
    hitBox[0][0] = playerCoord[0] + attackRangeX;
    hitBox[1][0] = playerCoord[0] + attackRangeX;
    hitBox[0][1] = playerCoord[1] + attackRangeY;
    hitBox[1][1] = playerCoord[1] + attackRangeY;

    _coord[0] = (hitBox[0][0] + hitBox[1][0])/2;
    _coord[1] = (hitBox[0][1] + hitBox[1][1])/2; 
}

void Attacks::setAttackMultiplier(int x){
    attackMultiplier = x;
}

void Attacks::findCombo(){
    //C'est pas trés propre mais je n'ai rien de mieux avec des std::string
    //Peut etre une récursive avec les états en impair et pair ?
    if(combo == "l"){
        state = 1;
        // std::cout << "Combo l!" << std::endl;
    }
    else if(combo == "h"){
        state = 2;
        // std::cout << "Combo h!" << std::endl;
        needToClearCombo = true;
    }
    else if(combo == "lh"){
        state = 2;
        // std::cout << "Combo lh!" << std::endl;
        needToClearCombo = true;
    }
    else if(combo == "ll"){
        state = 1;
        // std::cout << "Combo ll!" << std::endl;
    }
    else if(combo == "llh"){
        state = 5;
        needToClearCombo = true;
    }
    else if(combo == "lll"){
        state = 1;
        needToClearCombo = true;
    }
}

void Attacks::applyCombo(){
    //std::cout << "etat : " << state << std::endl;
    switch(state){
        case 0 :
            this->setOnScreen(false);
            break;
        
        case 1 :
            //std::cout << "Attaque simple" << std::endl;
            //std::cout << "directionX :" << directionX << " directionY :" << directionY << std::endl;
            attackDamage = 5 * attackMultiplier;
            range = 60;
            cdAttack = 400;
            break;
        
        case 2 : 
            //std::cout << "Attaque lourde" << std::endl;
            attackDamage = 10 *attackMultiplier;
            range = 40;
            cdAttack = 400;
            break;
            
        case 5 :
            // std::cout << "Combo llh!" << std::endl;
            attackDamage = 10 * attackMultiplier;
            range = 30;
            cdAttack = 200; 
            break;
        
        default :
            break;
    }
}

void Attacks::findDirection(int pushForceH, int pushForceB, int pushForceG, int pushForceD){
    // std::cout << "directionY :" << directionY <<  std::endl;
    if(pushForceH == 1){
        directionY =-1;
    }
    else if(pushForceB == 1){
        directionY =1;
    }
    else{
        directionY =0;
    }

    if(pushForceG == 1){
        directionX =-1;
    }
    else if(pushForceD == 1){
        directionX =1;
    }
    else{
        directionX =0;
    }
}

void Attacks::updateAttack(int attack){

    if(state == 0){
        if(attack !=0){
            switch(attack){
                case 1 :
                    //light attaque
                    //std::cout << "Light" << std::endl;
                    combo += "l";
                    break;

                case 2 :
                    //heavy attaque
                    //std::cout << "Heavy" << std::endl;
                    combo += "h";
                    break;

                default : 
                    std::cout << "Erreur nb attaque non reconnue" << std::endl;
                    break;
            }
            startCdAttack = stockeur->getGameTime();
            findCombo();
            applyCombo();
            findDirection(pushForceH, pushForceB, pushForceG, pushForceD);
            this->setOnScreen(true);
            // std::cout << "Attack combo is : "<< combo << std::endl; 
        }
    }
    else{
        std::cout << "Cooldown d'attaque en cours" << std::endl;
    }
}

void Attacks::reactionContact(Entite* other) {
    stockeur->getAudioManager()->playSound("punch");
    other->changePV(attackMultiplier);
}





// Fonctions de sauvegarde de l'objet (l'objet ne doit pas être enregistré)
std::string Attacks::serialize(std::string& toWrite) {
    return DONT_SERIALIZE_ME;
}

std::istringstream& Attacks::deSerialize(std::istringstream& iss) {
	return iss;
}