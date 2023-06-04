#include "Stockeur.hpp"
#include "Enemies.hpp"
#include "SkeletonShooter.hpp"
#include "BasicSkeleton.hpp"
#include "Input.hpp"


Stockeur::Stockeur(){}

// ADDER ----------------------------------------------------------------

void Stockeur::addSprites(Sprite* sp){
    if (printEverything) {
        std::cout << "added Sprite" << std::endl;
        std::cout << "taille de sprites : " << sprites.size()+1 << std::endl;
    }
    sprites.push_back(sp);
}

void Stockeur::addCircEntite(Entite* en){
    if (printEverything) {
        std::cout << "added circEntities" << std::endl;
        std::cout << "taille de circEntities : " << circEntities.size()+1 << std::endl;
    }
std::cout << circEntities.size() << std::endl;
    circEntities.push_back(en);
}

void Stockeur::addRectEntite(Entite* en){
    if (printEverything) {
        std::cout << "added rectEntities" << std::endl;
        std::cout << "taille de rectEntities : " << rectEntities.size()+1 << std::endl;
    }
    rectEntities.push_back(en);
}

void Stockeur::addEnemies(Enemies* en){
    if (printEverything) {
        std::cout << "added enemies" << std::endl;
        std::cout << "taille de enemies : " << enemies.size()+1 << std::endl;
    }
    enemies.push_back(en);
}


void Stockeur::addBullets(Bullets* bul){
    bullets.push_back(bul);
}


void Stockeur::addItem(Drop* dr){
    if (printEverything) {
        std::cout << "added items" << std::endl;
        std::cout << "taille de items : " << items.size()+1 << std::endl;
    }
    items.push_back(dr);
}

void Stockeur::addMc(Mc* j){
    if (printEverything) {
        std::cout << "added mc" << std::endl;
    }
    mc = j;
}

void Stockeur::addJoueur2(Joueur2* j){
    if (printEverything) {
        std::cout << "added j2" << std::endl;
    }
    j2 = j;
}


void Stockeur::addAudioManager(AudioManager* audioM){
    audioManager = audioM;
}

void Stockeur::addMenu(Menu* m){
    menu = m;
}

void Stockeur::addInput(Input* in){
    input = in;
}

// REMOVER ----------------------------------------------------------------

void Stockeur::removeSprites(Sprite* sp){
    if (printEverything) {
        std::cout << "removed sprites" << std::endl;
        std::cout << "taille de sprites : " << sprites.size()-1 << std::endl;
    }
    auto it = std::find(sprites.begin(), sprites.end(), sp);
    if (it != sprites.end()) {
        sprites.erase(it); 
    }

}

void Stockeur::removeCircEntite(Entite* en){
    if (printEverything) {
        std::cout << "removed circEntities" << std::endl;
        std::cout << "taille de circEntities : " << circEntities.size()-1 << std::endl;
    }
    auto it = std::find(circEntities.begin(), circEntities.end(), en);
    if (it != circEntities.end()) {
        circEntities.erase(it); 
    }
}

void Stockeur::removeRectEntite(Entite* en){
    if (printEverything) {
        std::cout << "removed rectEntities" << std::endl;
        std::cout << "taille de rectEntities : " << rectEntities.size()-1 << std::endl;
    }
    auto it = std::find(rectEntities.begin(), rectEntities.end(), en);
    if (it != rectEntities.end()) {
        rectEntities.erase(it); 
    }
}

void Stockeur::removeEnemies(Enemies* en){
    if (printEverything) {
        std::cout << "removed enemies" << std::endl;
        std::cout << "taille de enemies : " << enemies.size()-1 << std::endl;
    }
    auto it = std::find(enemies.begin(), enemies.end(), en);
    if (it != enemies.end()) {
        enemies.erase(it); 
    }
}

void Stockeur::removeItem(Drop* dr){

    if(printEverything) {
        std::cout << "removed enemies" << std::endl;
        std::cout << "taille de enemies : " << enemies.size()-1 << std::endl;
    }
    auto it = std::find(items.begin(), items.end(), dr);
    if (it != items.end()) {
        std::cout << "Erase en cours de l'item" << std::endl;
        items.erase(it); 
    }
    std::cout << "Checkpoint" << std::endl;
}


void Stockeur::removeBullet(Bullets* bullet) {
    auto it = std::find(bullets.begin(), bullets.end(), bullet);
    if (it != bullets.end()) {
        bullets.erase(it); 
    }
}


// GETTER ----------------------------------------------------------------

Mc* Stockeur::getMc() {
    return mc;
}

Joueur2* Stockeur::getJ2(){
    return j2;
}

std::vector<Sprite*>* Stockeur::getSpriteVector(){
    return &sprites;
}

std::vector<Entite*>* Stockeur::getCircEntiteVector(){
    return &circEntities;
}

std::vector<Entite*>* Stockeur::getRectEntiteVector(){
    return &rectEntities;
}

std::vector<Enemies*>* Stockeur::getEnemiesVector(){
    return &enemies;
}

std::vector<Drop*>* Stockeur::getItemVector(){
    return &items;
}

std::vector<Bullets*>* Stockeur::getBulletsVector(){
    return &bullets;
}

AudioManager* Stockeur::getAudioManager(){
    return audioManager;
}

Menu* Stockeur::getMenu(){
    return menu;
}

Input* Stockeur::getInput(){
    return input;
}

void Stockeur::deleteAllEnemies(){
    std::cout << "enemies.size : " << enemies.size() << std::endl;
    for(Enemies* en : enemies){
        delete en;
    }
    enemies.clear();
}


void Stockeur::deleteAll() {
    
    std::cout << "deleting all enemies (" << enemies.size() << ")" << std::endl;
    for(Enemies* en : enemies){
        delete en;
    }
    enemies.clear();

    // std::cout << "deleting all sprites (" << sprites.size() << ")" << std::endl;
    // for(Sprite* sp : sprites){
    //     delete sp;
    // }
    // sprites.clear();

    std::cout << "deleting all circEntities (" << circEntities.size() << ")" << std::endl;
    for(Entite* en : circEntities){
        delete en;
    }
    circEntities.clear();

    std::cout << "deleting all rectEntities (" << rectEntities.size() << ")" << std::endl;
    for(Entite* en : rectEntities){
        delete en;
    }
    rectEntities.clear();
    
    std::cout << "deleting all items (" << items.size() << ")" << std::endl;
    for(Drop* dp : items){
        delete dp;
    }
    items.clear();

    std::cout << "deleting all bullets (" << bullets.size() << ")" << std::endl;
    for(Bullets* bu : bullets){
        delete bu;
    }
    bullets.clear();
    
    // std::cout << "deleting mc" << std::endl;
    // if (mc != nullptr) delete mc;
    std::cout << "deleting j2" << std::endl;
    if (j2 != nullptr) delete j2;
    std::cout << "success" << std::endl;
    

    // for (unsigned int s=0; s < sprites.size(); s++) {
    //     delete(sprites[s]);
    //     s--;
    // }
}

void Stockeur::setMenuOff(bool toBe) {
    menuOff = toBe;
}

bool Stockeur::getMenuOff() {
    return menuOff;
}

void Stockeur::swapMenuOff() {
    menuOff = !menuOff;
}

void Stockeur::setMode(int toBe) {
    mode = toBe;
    switch(mode){
        case MODE_JEU :
            input->setMode(MODE_JEU);
            break;

        case MODE_MAP :
            input->setMode(MODE_JEU);
            break;

        case MODE_PAUSE :
            input->setMode(MODE_PAUSE);
            break;

        case MODE_MENU :
            input->setMode(MODE_MENU);
            break;

    }
}

int Stockeur::getMode() {
    return mode;
}

uint32_t& Stockeur::getGameTime(){
    return gameTime;
}


void Stockeur::saveGame() {
    std::string savedState = "";
    std::string serialized = "";
    std::string className = "";
    if (mc!= nullptr) {
        className = mc->serialize(serialized);
        className += CLASSNAME_SEPARATOR;
        savedState += className;
        savedState += serialized;
        savedState += "\n";
        savedState += OBJECT_SEPARATOR;
        
    }
    serialized = "";
    if (j2!= nullptr) {
        className = j2->serialize(serialized);
        className += CLASSNAME_SEPARATOR;
        savedState += className;
        savedState += serialized;
        savedState += "\n";
        savedState += OBJECT_SEPARATOR;
    }


    std::string pathComplet = PATH_TO_SAVE;
    pathComplet += "game.txt";
    std::fstream file(pathComplet, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
		file << savedState;
        file.close();
        std::cout << "Enregistrement terminé." << std::endl;
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
}



void Stockeur::loadSave(std::string path) {
    // deleteAll();
    std::cout << "LOADING ------------------------" << std::endl;
    std::string pathComplet = PATH_TO_SAVE + path;
    std::ifstream inputFile(pathComplet);

    if (inputFile.is_open()) {
        std::string content((std::istreambuf_iterator<char>(inputFile)),
                            (std::istreambuf_iterator<char>()));
        
        std::cout << "Contenu du fichier :\n" << content << std::endl;
        inputFile.close();

        // On lit le type de ce que l'on va construire
        std::istringstream iss(content);
        std::string objectToken;
        while (std::getline(iss, objectToken, OBJECT_SEPARATOR)) {
            std::cout << "on doit deserialiser :\n" << objectToken << std::endl;
            std::istringstream iss(objectToken);
            std::string classToken; // On va vérifier la classe à laquelle appartient l'objet
            if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                if (classToken == "Mc") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        mc = new Mc();

                        std::istringstream iss(classToken);
                        mc->deSerialize(iss);
                    };
                }
                
                else if (classToken == "Joueur2") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        j2 = new Joueur2();

                        std::istringstream iss(classToken);
                        j2->deSerialize(iss);
                    }
                }

                else if (classToken == "Sprite") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        Sprite* s = new Sprite(); // S'ajoute tout seul à sprites

                        std::istringstream iss(classToken);
                        s->deSerialize(iss);
                    }
                }

                else if (classToken == "Entite") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        Entite* e = new Entite(); // S'ajoute tout seul à sprites

                        std::istringstream iss(classToken);
                        e->deSerialize(iss);
                        e->hitBoxType(e->getIsCirc(), e->getIsRect());
                    }
                }
                
                else if (classToken == "Drop") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        Drop* e = new Drop(); // S'ajoute tout seul à sprites

                        std::istringstream iss(classToken);
                        e->deSerialize(iss);
                        e->hitBoxType(e->getIsCirc(), e->getIsRect());
                        e->addSprite("Drop");
                    }
                }
                
                else if (classToken == "SkeletonShooter") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        SkeletonShooter* e = new SkeletonShooter(); // S'ajoute tout seul aux listes appropriées

                        std::istringstream iss(classToken);
                        e->deSerialize(iss);
                    }
                }
                
                else if (classToken == "BasicSkeleton") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        BasicSkeleton* e = new BasicSkeleton(); // S'ajoute tout seul aux listes appropriées

                        std::istringstream iss(classToken);
                        e->deSerialize(iss);
                    }
                }
                
                else if (classToken == "Bullets") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        Bullets* e = new Bullets(); // S'ajoute tout seul aux listes appropriées

                        std::istringstream iss(classToken);
                        e->deSerialize(iss);
                    }
                }
            }
        }
        
    } else {
        std::cout << "Impossible d'ouvrir le fichier pour deserialisation" << std::endl;
        std::cout << "----> cherché à " << pathComplet << std::endl;
    }
    std::cout << "Fin loading" << std::endl;
}