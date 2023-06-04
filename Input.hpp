#ifndef INPUT_HPP
#define INPUT_HPP

#include "Mc.hpp"
#include "affichage.hpp"


class Input : public Sprite {
protected:
	static const States* etatsInput;
	
	int mouseX;
	int mouseY;

	float dashValue;

	std::vector<Controle*> controleList; // Liste d'objet implémentant Controle
										 // Ces objets sont appellés quand des touches sont appuyées

public:
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Input();

	virtual ~Input();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	static void initialisation();
	
	void update();

	void get_keypress();
	void get_otherkeypress();
	void doKeyDown(SDL_KeyboardEvent& event);
	void doKeyUp(SDL_KeyboardEvent& event);
	void mousePress(SDL_MouseButtonEvent& b);

	void doOtherKeyDown(SDL_KeyboardEvent &event);
	void get_menuKeypress();
	void doPauseKeyDown(SDL_KeyboardEvent &event);

	void addMe(Controle* toAdd);

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif