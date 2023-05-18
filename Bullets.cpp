#include "Bullets.hpp"


Bullets::Bullets(){

}

Bullets::Bullets(int state, float directX, float directY) {
    //Mettre l'hitbox
    dx = directX;
    dy = directY;
    depForce = BASICBULLETSPEED;
    _hauteur = 16;
    _largeur = 16;

    onScreen = true;
    states = &(etatsDeBullets);

    _coord[0] = joueur2->getX();
    _coord[1] = joueur2->getY();

    autoSetHitBox();
    addSprite();
    std::cout << "YEAHHHHH" << std::endl;
}

void Bullets::update(){
    Vector2D v(dx, dy);
    move(v);
    translate(v);
    //test si touche quoique ce soit (meme bords de la map)
}