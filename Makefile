CC = cc
OPTIONS = -Wall -Werror -Wextra -pthread
SOURCES = main.c \
					parsing/parsing.c \
					queue/queue.c \
					queue/queue_utils.c \
					devs/devs.c \
					devs/devs_utils.c \
					monitoring/monitoring.c
					# threads/threads.c \
					# devs/dongles.c
ARGS = 3 800 300 400 500 6 100 fifo
NAME = codexion

all: build

build:
	$(CC) $(OPTIONS) $(SOURCES) -o $(NAME)

run_error: build
	./codexion 8 -2 3 4 5 6 7 fifo

run: build
	./codexion $(ARGS)

debug: 
	$(CC) $(OPTIONS) $(SOURCES) -g -o $(NAME)
	gdb --args ./$(NAME) $(ARGS)

norm: build
	watch norminette .
