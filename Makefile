CC=gcc
all: main.c
	gcc main.c -l SDL2 -l SDL2main -l SDL2_mixer -o a.out