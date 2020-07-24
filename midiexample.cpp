/*
plays midi files from SOUNDS.DAT in Hugo(this also works with Nitemare 3D's SND.DAT)
*/

#include <SDL.h>
#undef main
#include <SDL_mixer.h>
#include "Datreader.h"
int main() {
    int MUSIC_INDEX = 0;

	Datreader sounds("SOUNDS.DAT");

    //init SDL2 stuff
    SDL_Window* window = SDL_CreateWindow("Hugo Music Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    //load in first data chunk as midi
    SDL_RWops* musicdata = SDL_RWFromMem((void*)sounds[MUSIC_INDEX].data, sounds[MUSIC_INDEX].length);
    Mix_Music* music = Mix_LoadMUS_RW(musicdata, 1);

    //play them tunes
    Mix_PlayMusic(music, -1);

    SDL_Event event;
    
    bool open = true;
    while (open) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {

                case SDL_WINDOWEVENT_CLOSE:   // exit game
                    open = false;
                    break;

                default:
                    break;
                }
            }

        }
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
