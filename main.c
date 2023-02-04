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
void musicFinishedPlayback();

int main(int argc, char *argv[])
{

  init();

  int f = 0;
  int d = 0;
  char *file = NULL;
  char *directory = NULL;



  const struct option long_options[] = {
      /*
        {"verbose",no_argument,&verbose_flag,1}
      */
      {"help", no_argument, 0, 'h'},
      {"file", required_argument, &f, 'f'},
      {"directory", required_argument, &d, 'd'},
      {0, 0, 0, 0}
  };

  int opt;

  if (argc <= 1)
  {
    fprintf(stderr, "No arguments provided!\nTry 'cplay --help' for more information.\n");
  }
  else
  {
    while ((opt = getopt_long(argc, argv, "d:f:h", long_options, NULL)) != -1)
    {
      printf("optarg %s\n",optarg);
      switch(opt){
        case 'h':
          print_help();
          break;
        case 'f':
       
          file = optarg;
          break;
        case 'd':
        
          directory = optarg;
          break;
       default:
          break;

      }
    }
  }


  if(f && d){
    printf("OPTION -f, --file and -d, --directory are given\n");
    printf("%s\n",directory);
    int valid = 0;
    char response;

    while(!valid)
    {
      printf("Enter one option [f\\d]: ");
      scanf(" %c",&response);

      if(response == 'd' || response == 'f'){
        valid = 1;
      }
      else
        printf("Wrong Input given press f for single file and d for directory option\n");
    }   

   
  }
  printf("%d\n %d",f,d);
 
  
   
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
