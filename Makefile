CC = cc
OPTIONS = -Wall -Werror -Wextra
SOURCES = main.c \
					parsing/*.c \
					devs/devs.c \
					devs/devs_utils.c \
					errors/errors.c
NAME = codexion

all: build

build:
	$(CC) $(OPTIONS) $(SOURCES) -o $(NAME)

run_error: build
	./codexion 8 2 3 -4 5 6 7 uihg

run: build
	./codexion 7 2 3 4 5 6 7 fifo
