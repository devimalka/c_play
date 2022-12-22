#ifndef FILE_HANDLE_H_INCLUDED
#define FILE_HANDLE_H_INCLUDED

struct song
{
  char *file_path;
  const char *artist;
  const char *title;
  struct song *next;
};

void load_file_directory(char *dir_path);
char * returnPath(char * file);

#endif
