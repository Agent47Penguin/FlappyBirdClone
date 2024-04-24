CC=gcc
CFLAGS=-Ilibraries/include -Wall -g
LDFLAGS=-Llibraries/lib
LIBS=-lmingw32 -lraylib -lopengl32 -lgdi32 -lwinmm
SRC=src/main.c
OBJ=$(SRC:src/%.c=build/%.o)
EXEC=build/main

all: $(EXEC)

$(EXEC): $(OBJ)
	mkdir -p build
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS) $(LIBS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f build/*.o build/$(notdir $(EXEC))

run: all
	./$(EXEC)
