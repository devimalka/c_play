#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "file_handle.c"
#include "songs.c"
#include "getoptions.c"

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
  int help_bool;

  int c;

  

  if (argc <= 1)
  {
    fprintf(stderr, "no arguments provided!\nTry 'cplay --help' for more information\n");
  }
  else
  {
    while ((c = getopt(argc, argv, "d:f:h")) != -1)
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
      case 'h':
        help_bool = true;
        break;
     

      default:
        break;
      }
    }
  }

  if (folder && file)
  {
    printf("Two Given Specifiy One Option\n");
    exit(1);
  }
  else if (folder)
  {
    load_file_directory(folder);
    Mix_HookMusicFinished(musicFinishedCallback);
    for (struct song *current = head; current->next != NULL; current = current->next)
    {
      play(current->file_path);
    }
  }
  else if (file)
  {
    play(returnPath(file));
  }
  else if(help_bool){
    puts("help needed");
    print_help();
  }

  // int count = 0;
  // load_file_directory(folder);
  // Mix_HookMusicFinished(musicFinishedCallback);
  // for (struct song *node = head; node; node = node->next)
  // {
  //   printf("%s\n", node->file_path);
  // }
  // for (struct song *node = head; node; node = node->next)
  // {
  //   printf("%s\n", node->file_path);
  //   printf("count is %d\n", count);
  //   count++;
  //   // Mix_Music *song = Mix_LoadMUS(node->file_path);
  //   // if (Mix_PlayMusic(song, 1) != 0)
  //   // {
  //   //   printf("something\n");
  //   // }
  //   // while (!SDL_QuitRequested())
  //   //   SDL_Delay(250);
  //   // Mix_FreeMusic(song);
  //   play(node->file_path);
  // }
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
