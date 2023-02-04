#include "songs.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>


// song playing function
int play(char *song)
{
    Mix_Music *music = NULL;
    music = Mix_LoadMUS(song);
    if (Mix_PlayMusic(music, 1) != 0)
    {
        fprintf(stderr,"Error Playing\n",Mix_GetError());
    }
    while (!SDL_QuitRequested())
        SDL_Delay(250);
    Mix_FreeMusic(music);
}

