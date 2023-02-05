#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>


#include "file_handle.c"
//#include "songs.c"
#include "getoptions.c"

//Mix_Music *music = NULL;



int main(int argc, char *argv[])
{

  //init();

  int f = 0;
  int d = 0;
  char * file = NULL;
  char * directory = NULL;



  const struct option long_options[] = {
      /*
        {"verbose",no_argument,&verbose_flag,1}
      */
      {"help", no_argument, 0, 'h'},
      {"file", required_argument, 0, 'f'},
      {"directory", required_argument, 0, 'd'},
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
      switch(opt){
        case 'h':
          print_help();
          break;
        case 'f':
          file = strdup(optarg);
          break;
        case 'd':
          directory = strdup(optarg);
          break;
   
        default:
          break;

      }
    }
  }


  if(f && d)
  {
    printf("OPTION -f, --file and -d, --directory are given\n");
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

  
   
}

