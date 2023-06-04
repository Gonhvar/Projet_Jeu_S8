#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Inc.hpp"
#include "AudioManager.hpp"

class Sprite;
class Entite;
class Enemies;
class Drop;
class Mc;
class Joueur2;
class AudioManager;
class Bullets;
class SkeletonShooter;
class BasicSkeleton;
class Menu;
class Input;

#define MODE_JEU 0
#define MODE_MAP 1
#define MODE_MAXNUM 2
#define MODE_MENU 3
#define MODE_PAUSE 4

#define PATH_TO_SAVE "save/"
#define OBJECT_SEPARATOR '*'
#define CLASSNAME_SEPARATOR '>'

class Stockeur {
protected:
    std::vector<Sprite*> sprites;
    std::vector<Entite*> circEntities;
    std::vector<Entite*> rectEntities;
    std::vector<Enemies*> enemies;
    std::vector<Drop*> items;

    std::vector<Bullets*> bullets;

    Mc* mc;
    Joueur2* j2;
    AudioManager* audioManager;
    Menu* menu;
    Input* input;

    uint32_t gameTime;

    bool menuOff = true; // Pas de menu de base
    int mode = MODE_JEU;

public:

    bool printEverything = 0; // Sert au debug X(

    Stockeur();

    void addSprites(Sprite* sp);
    void addCircEntite(Entite* en);
    void addRectEntite(Entite* en);
    void addEnemies(Enemies* en);
    void addItem(Drop* dr);
    void addBullets(Bullets* bul);

    void addMc(Mc* j);
    void addJoueur2(Joueur2* j);
    void addAudioManager(AudioManager* audioM);
    void addMenu(Menu* m);
    void addInput(Input* in);

    void removeSprites(Sprite* sp);
    void removeCircEntite(Entite* en);
    void removeRectEntite(Entite* en);
    void removeEnemies(Enemies* en);
    void removeItem(Drop* dr);
    void removeBullet(Bullets* bullet);

    Mc* getMc();
    Joueur2* getJ2();
    AudioManager* getAudioManager();
    Menu* getMenu();
    Input* getInput();
    
    std::vector<Sprite*>* getSpriteVector();
    std::vector<Entite*>* getCircEntiteVector();
    std::vector<Entite*>* getRectEntiteVector();
    std::vector<Enemies*>* getEnemiesVector();
    std::vector<Drop*>* getItemVector();
    std::vector<Bullets*>* getBulletsVector();


    void deleteAllEnemies();
    void deleteAll();

    void setMenuOff(bool toBe);
    bool getMenuOff();
    void swapMenuOff();

    void setMode(int toBe);
    int getMode();
    uint32_t& getGameTime();

    void saveGame();
    void loadSave(std::string path = "game.txt");
    void loadMc();
};

#endif
