#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]){


    char *file_dir;
    if(argc==1){
        printf("No File path provided exiting program!\n");
    }
    else {
      file_dir = argv[1];
    }

    DIR *dir;
    struct dirent *d;
    dir = opendir(file_dir);

    if(dir){
        while((d=readdir(dir)) != NULL){
            printf("%s\n",d->d_name);
        }
    }



}