#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"


class Menu : public Sprite {
protected :
    static const States* etatsMenu;
    int etat;

    //Nombre de selection possible dans le menu
    int max_menu;
public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Menu();
    // virtual ~Menu() override;
    /* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	static void initialisation();

    void update();

    void addToEtat(int e);
    void select();

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
