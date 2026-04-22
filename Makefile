prog: mani.o joueur.o animation.o backg.o
	gcc mani.o joueur.o animation.o backg.o -o prog2 `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf

mani.o: mani.c animation.h backg.h joueur.h
	gcc -c mani.c `sdl2-config --cflags`
	
joueur.o: joueur.c joueur.h animation.h
	gcc -c joueur.c `sdl2-config --cflags`

animation.o: animation.c animation.h
	gcc -c animation.c `sdl2-config --cflags`

backg.o: backg.c backg.h
	gcc -c backg.c `sdl2-config --cflags`
