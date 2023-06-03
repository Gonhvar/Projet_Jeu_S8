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
        std::cout << "Problèmes chargement son à " << Mix_GetError() << fullName << std::endl;
    }else{
        Mix_VolumeChunk(sound, volume);
        Mix_PlayChannel(-1, sound, 0);
    }
}

void AudioManager::playMusic(std::string name){
    std::string fullName = "Sound/" + name + ".mp3";
    Mix_Music* music = Mix_LoadMUS(fullName.c_str());

    if (music == nullptr) {
        // Error handling for loading the sound file
        // Display an error message, log, or exit the program
        std::cout << "Problèmes chargement musique à " << fullName << std::endl;
    }
    Mix_VolumeMusic(volume);
    Mix_PlayMusic(music, -1);
}