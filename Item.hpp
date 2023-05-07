#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <vector>

class Interactible {};
class SDL_Texture {};


std::string fichierImageItem[1] = { // doit peut-être static ???? En gros pour dire que cette variable globale n'a pas d'existence en-dehors de ce fichier. Mais qu'en est-il de Item.cpp ?
	"path to image de l'item 0"
};


class Item {
protected:
	Interactible* interactible = nullptr; // Apparence de l'Item s'il est dropé. On met une référence car plusieurs Item peuvent être regroupé sous la même apparence (comme dans minecraft)
	uint8_t num = 0; // Indique de quel Item il s'agit.
	unsigned int nbItem = 1; // Donne le nombre d'item (dans le jeu) que cet Item représente. Permet d'en regrouper du même type plus efficacement


public:
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Item();
	Item(int lequel, int combien);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void appear();
	void disappear();
};

#endif