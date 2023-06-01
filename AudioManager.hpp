#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "Inc.hpp"

class AudioManager {
protected:
	int volume;
	
public:
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	AudioManager();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void playSound(std::string name);
};

#endif