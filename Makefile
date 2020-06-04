BIN     = ./bin
INCLUDE = ./include
LIB     = ./lib
OBJ     = ./obj
SRC     = ./src
TESTS   = ./src/tests

LIBS_FILES  = $(OBJ)/dynamic_string.o
TESTS_FILES = $(BIN)/test1

CC    = gcc
FLAGS = -O3 -Wall -std=c99
LIBS  = -L $(LIB) -lm -ldystr

all: dirs libdystr $(TESTS_FILES)

libdystr: dirs $(LIBS_FILES)
	ar -rcs $(LIB)/libdystr.a $(OBJ)/*.o

clean:
	rm -rf $(BIN)
	rm -rf $(LIB)
	rm -rf $(OBJ)

dirs:
	mkdir -p $(BIN) $(LIB) $(OBJ)

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(TESTS)/%.c
	$(CC) $(FLAGS) $< -I $(INCLUDE) $(LIBS) -o $@