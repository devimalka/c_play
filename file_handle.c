#include "file_handle.h"
#include <stdlib.h>
#include <dirent.h>
#include <libgen.h>

struct song *head = NULL;
struct song *node = NULL;

void load_file_directory(char *dir_path)
{

    DIR *dir;
    struct dirent *d;
    dir = opendir(dir_path);

    if (dir)
    {
        while ((d = readdir(dir)) != NULL)
        {
           
            if (d->d_type == DT_REG)
            {
                char *extension = strrchr(d->d_name, '.');
                if (extension && (strcmp(extension, ".mp3")) == 0)
                {
                    char * test =find_endwith_slash(dir_path,d->d_name);

                    printf("Dir is %s file is %s result is %s\n",dir_path,d->d_name,test);
                    node = malloc(sizeof(struct song));

                    if (!node)
                    {
                        printf("unable to allocate memeory");
                    }
                    else
                    {
                        char * fpp;
                        int string_length = strlen(dir_path); //  take the string length to check the last character of the given directory.
                        // if (dir_path[string_length - 1] != '/')
                        // {
                        //     sprintf(fpp, "%s/%s", dir_path, d->d_name); // if given directory last character is not "/" the "/" character will be added.
                        // }
                        // else
                        //     sprintf(fpp, "%s%s", dir_path, d->d_name);

                        fpp = find_endwith_slash(dir_path,d->d_name);
                            
                        node->file_path = strdup(fpp);

                        node->next = head;
                        head = node;
                    }
                }
            }
        }
    }
}

char *returnPath(char *file)
{
    char *path = realpath(file, NULL);
    if (path == NULL)
    {
        fprintf(stderr, "Error Full Path\n");
    }
    else
    {
        return path;
        free(path);
    }
}

char * find_endwith_slash(char *dir_path, char *file_name)
{
    char full_path[1024];
    if (dir_path[strlen(dir_path) - 1] != '/')
    {
        sprintf(full_path, "%s/%s", dir_path, file_name);
    }
    else
    {
        sprintf(full_path, "%s%s", dir_path, file_name);
    }

    char * full_name = malloc(strlen(full_path) * sizeof(char));
    full_name = full_path;

    return full_name;
    free(full_name);


}
