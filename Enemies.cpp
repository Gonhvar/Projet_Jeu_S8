#include "Enemies.hpp"

Enemies::Enemies(){}

Enemies::Enemies(std::string& spriteName, uint8_t nbStates, std::vector<uint8_t>& nbFPE) : Drop(spriteName, nbStates, nbFPE) {}


void Enemies::update() {
    deplacementBehaviour();
    attackBehaviour();
}