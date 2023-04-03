#include "Sprite.h"

double* Sprite::getCoord() {
	return coord;
}

void Sprite::setCoord(double& x, double& y, double& theta) {
	coord[0] = x;
	coord[1] = y;
	coord[2] = theta;
}
void Sprite::setCoord(double* coordonnees) {
	coord[0] = coordonnees[0];
	coord[1] = coordonnees[1];
	coord[2] = coordonnees[2];
}

float* Sprite::getLargeur() {

}
void Sprite::setLargeur(float L);
float* Sprite::getHauteur();
void Sprite::setHauteur(float H);