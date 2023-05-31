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
	Drop() = default;
	Drop(std::vector<int> items, std::vector<int> taux, int x, int y);
	virtual ~Drop() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();
	void selectItem();
	void getItem();

	virtual void reactionContact(Entite* other);
};

#endif