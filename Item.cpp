#include "Item.hpp"
#include "Interactible.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Item::Item() {
	/*
	interactible = nullptr;
	num = 0;
	nbItem = 1;
	*/
}

Item::Item(int lequel, int combien) {
	num = lequel;
	nbItem = combien;
	interactible = new Interactible(fichierImageItem[lequel]);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Item::appear() {
	interactible->appear();
}

void Item::disappear() {
	interactible->disappear();
}