BIN     = ./bin
LIB     = ./lib
OBJ     = ./obj
SRC     = ./src
TEST    = ./src/tests
INCLUDE = ./include

EXS   = c
CC    = gcc
FLAGS = -O3 -Wall -std=c99
LIBS  = -L $(LIB) -lm -lcemdutil

ARRAY_LIST     = $(OBJ)/cemdutil/array_list.o
DYNAMIC_STRING = $(OBJ)/cemdutil/dynamic_string.o
LINKED_LIST    = $(OBJ)/cemdutil/linked_list.o

SUB_DIRS   = $(OBJ)/cemdutil
LIB_FILES  = $(ARRAY_LIST) $(DYNAMIC_STRING) $(LINKED_LIST)
TEST_FILES = $(BIN)/test1

all: dirs libcemdutil $(TEST_FILES)

libcemdutil: dirs $(LIB_FILES)
	ar -rcs $(LIB)/libcemdutil.a $(LIB_FILES)

dirs:
	mkdir -p $(BIN) $(LIB) $(OBJ)
	mkdir -p $(SUB_DIRS)

clean:
	rm -rf $(BIN)
	rm -rf $(LIB)
	rm -rf $(OBJ)

$(OBJ)/%.o: $(SRC)/%.$(EXS)
	$(CC) $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(TEST)/%.$(EXS)
	$(CC) $(FLAGS) $< -I $(INCLUDE) $(LIBS) -o $@