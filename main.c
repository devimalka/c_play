#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "file_handle.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

struct tags
{
  const char *artist;
} tags;

Mix_Music *music = NULL;

bool loadmedia(char *filepath);
void play();
void init();
void load_file_directory(char *dir_path);

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

  // char *file = argv[1];

  // bool status = loadmedia(file);
  // if(status){
  //   printf("%s - %s\n",Mix_GetMusicArtistTag(music),Mix_GetMusicTitleTag(music));
  //   if(Mix_PlayMusic(music,1)){
  //     printf("something wrong");
  //     Mix_FreeMusic(music);

  //   }

  // }

  // while(!SDL_QuitRequested())
  // SDL_Delay(250);
}

bool loadmedia(char *file_path)
{

  bool success = false;
  if (file_path)
  {
    music = Mix_LoadMUS(file_path);
    success = true;
  }
  else
  {
    printf("File Loaded Failed\n");
  }

  return success;
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
