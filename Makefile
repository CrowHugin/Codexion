CC = cc
OPTIONS = -Wall -Werror -Wextra
SOURCES = main.c parsing/*.c
NAME = codexion

all: build

build:
	$(CC) $(OPTIONS) $(SOURCES) -o $(NAME)

run_error: build
	./codexion 1 2 3 4 5 6 -7 uihg

run: build
	./codexion 1 2 3 4 5 6 7 8
