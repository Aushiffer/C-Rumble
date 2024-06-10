CCFLAGS = -Wall -Wextra -pedantic
CC = gcc
ALLEGRO_LIBS = -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image
PROGRAM = C-Rumble

all: $(PROGRAM)

$(PROGRAM): main.o
	$(CC) -o $(PROGRAM) main.o $(CCFLAGS) $(ALLEGRO_LIBS)

main.o: src/main.c
	$(CC) -c src/main.c $(CCFLAGS) $(ALLEGRO_LIBS)

run: 
	./$(PROGRAM)

clean:
	rm -f *.o

purge:
	rm -f *.ch *.o $(PROGRAM)