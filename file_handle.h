#ifndef FILE_HANDLE_H_INCLUDED
#define FILE_HANDLE_H_INCLUDED

struct song
{
  char *file_path;
  struct song *next;
};

void load_file_directory(char *dir_path);

char * returnPath(char * file);

char * find_endwith_slash(char *dir_path, char *file_name);


#endif
