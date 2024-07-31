CCFLAGS = -std=c99 -g -Wall -Wextra -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image
PROGRAM = C-Rumble
OBJ = obj
BIN = bin
SRC = src

all: $(BIN)/$(PROGRAM)

$(BIN)/$(PROGRAM): $(OBJ)/main.o $(OBJ)/game_states.o $(OBJ)/draw.o $(OBJ)/destroy_resources.o $(OBJ)/selector.o $(OBJ)/fighter.o $(OBJ)/controller.o $(OBJ)/hitbox.o $(OBJ)/load_spriteset.o $(OBJ)/handle_pause.o
	$(CC) -o $@ $^ $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/main.o:
	$(CC) -c $(SRC)/main.c -o $(OBJ)/main.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/game_states.o: $(SRC)/game_states/game_states.h $(SRC)/game_states/game_states.c
	$(CC) -c $(SRC)/game_states/game_states.c -o $(OBJ)/game_states.o $(CCFLAGS)

$(OBJ)/draw.o: $(SRC)/draw/draw.h $(SRC)/draw/draw.c
	$(CC) -c $(SRC)/draw/draw.c -o $(OBJ)/draw.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/destroy_resources.o: $(SRC)/destroy_resources/destroy_resources.h $(SRC)/destroy_resources/destroy_resources.c
	$(CC) -c $(SRC)/destroy_resources/destroy_resources.c -o $(OBJ)/destroy_resources.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/selector.o: $(SRC)/selector/selector.h  $(SRC)/selector/selector.c
	$(CC) -c $(SRC)/selector/selector.c -o $(OBJ)/selector.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/fighter.o: $(SRC)/fighter/fighter.h $(SRC)/fighter/fighter.c
	$(CC) -c $(SRC)/fighter/fighter.c -o $(OBJ)/fighter.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/controller.o: $(SRC)/controller/controller.h $(SRC)/controller/controller.c
	$(CC) -c $(SRC)/controller/controller.c -o $(OBJ)/controller.o $(CCFLAGS)

$(OBJ)/hitbox.o: $(SRC)/hitbox/hitbox.h $(SRC)/hitbox/hitbox.c
	$(CC) -c $(SRC)/hitbox/hitbox.c -o $(OBJ)/hitbox.o $(CCFLAGS)

$(OBJ)/load_spriteset.o: $(SRC)/load_spriteset/load_spriteset.h $(SRC)/load_spriteset/load_spriteset.c
	$(CC) -c $(SRC)/load_spriteset/load_spriteset.c -o $(OBJ)/load_spriteset.o $(CCFLAGS) $(ALLEGRO_LIBS)

$(OBJ)/handle_pause.o: $(SRC)/pause_menu/handle_pause.h $(SRC)/pause_menu/handle_pause.c
	$(CC) -c $(SRC)/pause_menu/handle_pause.c -o $(OBJ)/handle_pause.o $(CCFLAGS) $(ALLEGRO_LIBS)

run:
	./$(BIN)/$(PROGRAM)

test_run:
	make purge && make && make run

clean:
	rm -f $(OBJ)/*.o

purge: clean
	rm -f $(BIN)/$(PROGRAM)