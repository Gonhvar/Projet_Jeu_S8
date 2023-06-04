#include "Stockeur.hpp"
// #include "Enemies.hpp"
#include "SkeletonShooter.hpp"
#include "BasicSkeleton.hpp"
#include "Input.hpp"
#include "SpawnPoint.hpp"


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

void Stockeur::addItem(Drop* dr){
    if (printEverything) {
        std::cout << "added items" << std::endl;
        std::cout << "taille de items : " << items.size()+1 << std::endl;
    }
    items.push_back(dr);
}

void Stockeur::addBullets(Bullets* bul){
    if (printEverything) {
        std::cout << "added bullets" << std::endl;
        std::cout << "taille de bullets : " << bullets.size()+1 << std::endl;
    }
    bullets.push_back(bul);
}

void Stockeur::addSpawn(SpawnPoint* sp){
    if (printEverything) {
        std::cout << "added spawnPoints" << std::endl;
        std::cout << "taille de spawnPoints : " << spawnPoints.size()+1 << std::endl;
    }
    spawnPoints.push_back(sp);
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
    if (printEverything) {
        std::cout << "removed items" << std::endl;
        std::cout << "taille de items : " << items.size()-1 << std::endl;
    }
    auto it = std::find(items.begin(), items.end(), dr);
    if (it != items.end()) {
        items.erase(it); 
    }
}

void Stockeur::removeBullet(Bullets* bul) {
    if (printEverything) {
        std::cout << "removed bullets" << std::endl;
        std::cout << "taille de bullets : " << bullets.size()-1 << std::endl;
    }
    auto it = std::find(bullets.begin(), bullets.end(), bul);
    if (it != bullets.end()) {
        bullets.erase(it); 
    }
}

void Stockeur::removeSpawn(SpawnPoint* sp) {
    if (printEverything) {
        std::cout << "removed spawnPoints" << std::endl;
        std::cout << "taille de spawnPoints : " << spawnPoints.size()-1 << std::endl;
    }
    auto it = std::find(spawnPoints.begin(), spawnPoints.end(), sp);
    if (it != spawnPoints.end()) {
        spawnPoints.erase(it); 
    }
}


// GETTER ----------------------------------------------------------------

Mc* Stockeur::getMc() {
    return mc;
}

Joueur2* Stockeur::getJ2(){
    return j2;
}

AudioManager* Stockeur::getAudioManager(){
    return audioManager;
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

std::vector<SpawnPoint*>* Stockeur::getSpawnVector(){
    return &spawnPoints;
}



void Stockeur::setInputLoaded(bool toBe) {
    inputLoaded = toBe;
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
    // Supprime tous les objets de la carte (mais pas d'AudioManager)

    // On supprime d(abord les enemies comme ça ils font spawner leur Drop sans géner la suppression
    deleteAllEnemies();

    // Ensuite on peut supprimer tout le reste
    std::cout << "deleting all sprites (" << sprites.size() << ")" << std::endl;
    for (unsigned int s=0; s < sprites.size(); s++) {
        std::cout << "Deleting (" << sprites[s]->getStates()->spriteName << ")" << std::endl;
        delete(sprites[s]);
        s--;
    }
    sprites.clear();
    circEntities.clear();
    rectEntities.clear();
    items.clear();
    bullets.clear();
    mc = nullptr;
    j2 = nullptr;
}

uint32_t& Stockeur::getGameTime(){
    return gameTime;
}


void Stockeur::saveGame() {
    std::string savedState = "";
    std::string serialized = "";
    std::string className = "";

    for (Sprite* s : sprites) { // On assume que tout ce qui doit être sauvegardé est dans la liste sprite
                                // Notamment parce que tous les objets des autres liste descendent de Sprite
        className = s->serialize(serialized);
        if (className != DONT_SERIALIZE_ME) {
            className += CLASSNAME_SEPARATOR;
            savedState += className;
            savedState += serialized;
            savedState += "\n";
            savedState += OBJECT_SEPARATOR;

            serialized = "";
        }
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
                        // e->hitBoxType(e->getIsCirc(), e->getIsRect());
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
                
                else if (classToken == "SpawnPoint") {
                    if (std::getline(iss, classToken, CLASSNAME_SEPARATOR)) {
                        SpawnPoint* s = new SpawnPoint(); // S'ajoute tout seul aux listes appropriées

                        std::istringstream iss(classToken);
                        s->deSerialize(iss);
                    }
                }
                else {
                    std::cout << "Nom de classe non reconnu durant le chargement : " << classToken << std::endl;
                }
            }
        }
        
        if (mc == nullptr) {
            mc = new Mc();
        }
        if (j2 == nullptr) {
            j2 = new Joueur2();
        }
    } else {
        std::cout << "Impossible d'ouvrir le fichier pour deserialisation" << std::endl;
        std::cout << "----> cherché à " << pathComplet << std::endl;
    }
    std::cout << "Fin loading" << std::endl;
}