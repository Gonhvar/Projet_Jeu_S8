#include "AudioManager.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
AudioManager::AudioManager(){
    
    //Init de l'audio
	SDL_Init(SDL_INIT_AUDIO);
	// Initialize any other audio formats you plan to use
    Mix_Init(MIX_INIT_MP3);  
	//A verifier 
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //On est à 50% du son max
    volume = MIX_MAX_VOLUME / 2;
}



void AudioManager::playSound(std::string name){

    std::string fullName = "Sound/" + name + ".mp3";
    Mix_Chunk* sound = Mix_LoadWAV(fullName.c_str());

    if (sound == nullptr) {
        // Error handling for loading the sound file
        // Display an error message, log, or exit the program
        std::cout << "Problémes chargement son" << std::endl;
    }
    Mix_VolumeChunk(sound, volume);

    Mix_PlayChannel(-1, sound, 0);
}