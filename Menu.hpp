#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"


class Menu : public Sprite {
protected :
    int mode;
    int etat;

    //Nombre de selection possible dans le menu
    int max_menu;
public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Menu();
    // virtual ~Menu() override;
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void update();

    void setMode(int m);
    void addToEtat(int e);
};

#endif
