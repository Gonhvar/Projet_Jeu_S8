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
    static const States* etatsSpawnPoint;
    int i;
    int phase;
    int wave;
    Uint32 FrameStartTimeMs;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    SpawnPoint();
    SpawnPoint(float x, float y,  int wave);

    virtual ~SpawnPoint();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	static void initialisation();

    void spawn(int number, int select, float timing);
    void spawnWave(int selectWave);
    void update();

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
