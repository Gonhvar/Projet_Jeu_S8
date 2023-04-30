#ifndef SPAWNPOINT_HPP
#define SPAWNPOINT_HPP

#pragma once
#include "Venera.hpp"

class Venera;

class SpawnPoint : public Entite {

protected :
    Venera* _main;
    int i;
    int phase;
    Uint32 FrameStartTimeMs;
public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    SpawnPoint();
    SpawnPoint(float x, float y, Venera* main);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void spawn(int select, float timing);
    void spawnWave(int selectWave);
    void update();

};

#endif