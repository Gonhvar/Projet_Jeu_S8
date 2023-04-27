#ifndef KILLABLE_HPP
#define KILLABLE_HPP

#pragma once
#include "Entite.hpp"

class Killable : Entite { // a priori c'est une classe virtuelle pure
                // Parce qu'il n'y a pas littérallement de Killable.
                // Il y a des mobs spécifiques qui sont des Killable, le Mc aussi
private :
    Killable(std::string& spriteName);

protected :

    std::vector<Entite*> entite;

public :
}

#endif