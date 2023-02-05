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


void init()
{

  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    printf("Couldn't initialize SDL: %s\n", SDL_GetError());
  }

  if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
  {
    fprintf(stderr, "could not initialized mixer\n", Mix_GetError());
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    fprintf(stderr, "SDL_mixer could not be initialized %s\n", Mix_GetError());
  }
}


void musicFinishedCallback()
{
  // Get the next song in the linked list and play it
  if (node->next)
  {
    node = node->next;
    Mix_PlayMusic(Mix_LoadMUS(node->file_path), 1);
  }
  // If there are no more songs in the linked list, stop the music
  else
  {
    Mix_HaltMusic();
  }
}
