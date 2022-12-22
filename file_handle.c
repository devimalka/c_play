#include "file_handle.h"
#include <stdlib.h>
#include <dirent.h>

struct song *head = NULL;
struct song *node = NULL;

void load_file_directory(char *dir_path)
{

    DIR *dir;
    struct dirent *d;
    dir = opendir(dir_path);

    int count = 0;
    if (dir)
    {
        while ((d = readdir(dir)) != NULL)
        {
            if (d->d_type == DT_REG)
            {
                char *extension = strrchr(d->d_name, '.');
                if (extension && (strcmp(extension, ".mp3")) == 0)
                {
                    count++;
                    node = malloc(sizeof(struct song));

                    if (!node)
                    {
                        printf("unable to allocate memeory");
                    }

                    char fpp[1024];
                    int string_length = strlen(dir_path); //  take the string length to check the last character of the given directory.
                    if (dir_path[string_length - 1] != '/')
                    {
                        sprintf(fpp, "%s/%s", dir_path, d->d_name); // if given directory last character is not "/" the "/" character will be added.
                    }
                    else
                        sprintf(fpp, "%s%s", dir_path, d->d_name);

                    node->file_path = strdup(fpp);

                    node->next = head;
                    head = node;
                }
            }
        }
    }

    printf("count is %d\n", count);
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
