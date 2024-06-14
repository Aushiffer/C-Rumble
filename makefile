CCFLAGS = -Wall -Wextra -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image
PROGRAM = C-Rumble

all: $(PROGRAM)

$(PROGRAM): main.o game_states.o draw.o
	$(CC) -o $(PROGRAM) main.o game_states.o draw.o $(CCFLAGS) $(ALLEGRO_LIBS)

main.o: src/main.c
	$(CC) -c src/main.c $(CCFLAGS) $(ALLEGRO_LIBS)

game_states.o: src/game_states/game_states.c src/game_states/game_states.h
	$(CC) -c src/game_states/game_states.c $(CCFLAGS)

draw.o: src/draw/draw.c src/draw/draw.h
	$(CC) -c src/draw/draw.c $(CCFLAGS) $(ALLEGRO_LIBS)

run: 
	./$(PROGRAM)

clean:
	rm -f *.o

purge:
	rm -f *.ch *.o $(PROGRAM)