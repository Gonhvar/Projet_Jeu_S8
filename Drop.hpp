#ifndef DROP_HPP
#define DROP_HPP

#include "Entite.hpp"

class Drop : public Entite {
protected:
	int item;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Drop() = default;
	Drop(std::vector<int> items, std::vector<int> taux, int x, int y);
	virtual ~Drop() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();
	void selectItem();
	void getItem();

};

#endif