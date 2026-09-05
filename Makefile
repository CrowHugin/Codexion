CC = cc
OPTIONS = -Wall -Werror -Wextra -pthread
SOURCES = main.c \
					parsing/*.c \
					devs/devs.c \
					devs/devs_utils.c \
					devs/dongles.c \
					threads/threads.c \
					monitoring/monitoring.c \
					queue/queue.c
ARGS = 3 200 300 400 500 6 100 fifo
NAME = codexion

all: build

build:
	$(CC) $(OPTIONS) $(SOURCES) -o $(NAME)

run_error: build
	#./codexion 8 2 3 -4 5 6 7 uihg
	#./codexion 8 -2 3 -4 5 6 7 fifo
	./codexion 8 2 3 4 5 6 7

run: build
	./codexion $(ARGS)

debug: 
	$(CC) $(OPTIONS) $(SOURCES) -g -o $(NAME)
	gdb --args ./$(NAME) $(ARGS)

norm: build
	watch norminette .
