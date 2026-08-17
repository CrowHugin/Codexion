CC = cc
OPTIONS = -Wall -Werror -Wextra
SOURCES = main.c parsing/*.c devs/devs.c
NAME = codexion

all: build

build:
	$(CC) $(OPTIONS) $(SOURCES) -o $(NAME)

run_error: build
	./codexion 8 2 3 -4 5 6 7 uihg

run: build
	./codexion 3 2 3 4 5 6 7 8
