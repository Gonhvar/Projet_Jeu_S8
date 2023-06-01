#ifndef SPAWNPOINT_HPP
#define SPAWNPOINT_HPP

#include "Venera.hpp"

class Venera;

/*
const States etatsDesSpawnPoint = {
	"SpawnPoint",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class SpawnPoint : public Entite {

protected :
    int i;
    int phase;
    int wave;
    Uint32 FrameStartTimeMs;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    SpawnPoint();
    SpawnPoint(float x, float y,  int wave);

    virtual ~SpawnPoint() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void spawn(int number, int select, float timing);
    void spawnWave(int selectWave);
    void update();

};

#endif
