CCFLAGS = -O3 -std=c99 -g -Wall -Wextra -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image
PROGRAM = C-Rumble

all: $(PROGRAM)

$(PROGRAM): main.o game_states.o draw.o destroy_resources.o selector.o fighter.o controller.o hitbox.o load_spriteset.o handle_pause.o
	$(CC) -o $(PROGRAM) main.o game_states.o draw.o destroy_resources.o selector.o fighter.o controller.o hitbox.o load_spriteset.o handle_pause.o $(CCFLAGS) $(ALLEGRO_LIBS)

main.o:
	$(CC) -c src/main.c $(CCFLAGS) $(ALLEGRO_LIBS)

game_states.o:
	$(CC) -c src/game_states/game_states.c $(CCFLAGS)

draw.o:
	$(CC) -c src/draw/draw.c $(CCFLAGS) $(ALLEGRO_LIBS)

destroy_resources.o:
	$(CC) -c src/destroy_resources/destroy_resources.c $(CCFLAGS) $(ALLEGRO_LIBS)

selector.o:
	$(CC) -c src/selector/selector.c $(CCFLAGS) $(ALLEGRO_LIBS)

fighter.o:
	$(CC) -c src/fighter/fighter.c $(CCFLAGS) $(ALLEGRO_LIBS)

controller.o:
	$(CC) -c src/controller/controller.c $(CCFLAGS)

hitbox.o:
	$(CC) -c src/hitbox/hitbox.c $(CCFLAGS)

load_spriteset.o:
	$(CC) -c src/load_spriteset/load_spriteset.c $(CCFLAGS) $(ALLEGRO_LIBS)

handle_pause.o:
	$(CC) -c src/pause_menu/handle_pause.c $(CCFLAGS) $(ALLEGRO_LIBS)

run:
	./$(PROGRAM)

test_run:
	make purge && make && make run

clean:
	rm -f *.o

purge:
	rm -f *.gch *.o $(PROGRAM)