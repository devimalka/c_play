#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "file_handle.c"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music *music = NULL;

void init();

int main(int argc, char *argv[])
{

  char *file_path;

  if (argc <= 1)
  {
    fprintf(stderr, "no arguments provided!\n");
  }
  else
  {
    file_path = argv[2];
  }

  if (file_path)
  {
    load_file_directory(file_path);
  }

  init();
  int count = 0;

  for (struct song *node = head; node; node = node->next)
  {
    printf("%s\n", node->file_path);
  }
  for (struct song *node = head; node; node = node->next)
  {
    printf("%s\n", node->file_path);
    printf("count is %d\n", count);
    count++;
    Mix_Music *song = Mix_LoadMUS(node->file_path);
    if (Mix_PlayMusic(song, 1) != 0)
    {
      printf("something\n");
    }
    while (!SDL_QuitRequested())
      SDL_Delay(250);
    Mix_FreeMusic(song);
  }
}

void init()
{

  bool success;
  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    printf("Couldn't initialize SDL: %s\n", SDL_GetError());
    success = false;
  }

  if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
  {
    fprintf(stderr, "could not initialized mixer\n", Mix_GetError());
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("SDL_mixer could not be initialized %s\n", Mix_GetError());
    success = false;
  }
}
