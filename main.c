#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "file_handle.c"
#include "songs.c"

Mix_Music *music = NULL;

void init();

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

int main(int argc, char *argv[])
{
  init();

  char *file = NULL;
  int file_bool = false;
  char *folder = NULL;
  int folder_bool = false;

  int c;

  while ((c = getopt(argc, argv, "d:f:")) != -1)
  {
    switch (c)
    {
    case 'f':
      file = optarg;
      file_bool = true;
      break;
    case 'd':
      folder = optarg;
      folder_bool = true;
      break;

    default:
      break;
    }
  }

  if (argc <= 1)
  {
    fprintf(stderr, "no arguments provided!\n");
  }
  else if (folder && file)
  {
    int loop = true;
    int choice;
    while (loop)
    {
      printf("argument -d and -f given\nChose One Option\n1.[-d]:%s\n2.[-f]:%s\nChoice[1/2]:", folder, file);
      scanf("%d", &choice);
      if (choice > 2)
      {
        printf("Invalid Option\n");
        continue;
      }
      else
        loop = false;
    }
    if (choice == 1)
    {
    }
    if (choice == 2)
    {

      char *path = returnPath(file);
      printf("%s\n", path);
      play(path);
    }
  }

  int count = 0;
  load_file_directory(folder);
  Mix_HookMusicFinished(musicFinishedCallback);
  for (struct song *node = head; node; node = node->next)
  {
    printf("%s\n", node->file_path);
  }
  for (struct song *node = head; node; node = node->next)
  {
    printf("%s\n", node->file_path);
    printf("count is %d\n", count);
    count++;
    // Mix_Music *song = Mix_LoadMUS(node->file_path);
    // if (Mix_PlayMusic(song, 1) != 0)
    // {
    //   printf("something\n");
    // }
    // while (!SDL_QuitRequested())
    //   SDL_Delay(250);
    // Mix_FreeMusic(song);
    play(node->file_path);
  }
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
