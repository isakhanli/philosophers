NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

SRC = 	./src/main.c\
		./src/utils.c\
		./src/philo_utils.c\
		./src/start_threads.c\
		./src/controller.c\

OBJS = $(SRC:.c=.o)

INCLUDES = ./includes/philo.h

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	$(CC) $(CFLAGS) $(SRC) -o philo

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: make clean fclean re
