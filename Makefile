CC=gcc
OBJ=obj
SRC=src
BIN=bin
ifeq ($(OS),Windows_NT)
	CFLAGS=-O -DWIN32 -Isrc
else
	CFLAGS=-O -Isrc
endif


all: $(BIN)/spellcheck.exe

$(BIN)/spellcheck.exe: $(OBJ)/main.o $(OBJ)/search_tree_parser.o $(OBJ)/search_tree.o $(OBJ)/io.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ)/main.o: $(OBJ)/search_tree_parser.o $(OBJ)/search_tree.o

$(OBJ)/search_tree_parser.o: $(OBJ)/search_tree.o

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $^ -o $@ -c
