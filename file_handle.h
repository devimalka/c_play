struct song{
  char *file_path;
  const char *artist;
  const char *title;
  struct song * next;
};


#include <stdlib.h>


struct song * head = NULL;
// list files on directory
void load_file_directory(char *dir_path) {

  DIR *dir;
  struct dirent *d;
  dir = opendir(dir_path);

  int count = 0;
  if (dir) {
    while ((d = readdir(dir)) != NULL) {
      if (d->d_type == DT_REG) {
        char *extension = strrchr(d->d_name,'.');
        if(extension && (strcmp(extension,".mp3"))==0){
          count++;
          struct song * node = malloc(sizeof(struct song));
          if(!node){
            printf("unable to allocate memeory");
          }

            char fpp[1024];
            sprintf(fpp,"%s/%s",dir_path,d->d_name);
            node->file_path = strdup(fpp);

            node->next = head;
            head = node;
        }
      }
    }
  }



  printf("count is %d\n",count);
}