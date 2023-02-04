CC=gcc
CFLAGS = -lSDL2 -lSDL2main -lSDL2_mixer 
all: main.c
	$(CC) $(CFLAGS) -o a.out main.c
	