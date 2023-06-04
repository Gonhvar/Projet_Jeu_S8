#ifndef DROP_HPP
#define DROP_HPP

#include "Entite.hpp"

class Drop : public Entite {
protected:
	int item;
	bool stillInUse;
	uint32_t cd;
	uint32_t startUse;
	
	Entite* otherEntite;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Drop();
	Drop(std::vector<int> items, std::vector<int> taux, int x, int y);
	virtual ~Drop() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();
	void selectItem();
	virtual void reactionContact(Entite* other);

	void resetColor();

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif