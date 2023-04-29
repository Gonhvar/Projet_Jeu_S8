#include "Enemies.hpp"

Enemies::Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Drop(sName, nbE, nbFPE) {}


void Enemies::update() {
    deplacementBehaviour();
    attackBehaviour();
}