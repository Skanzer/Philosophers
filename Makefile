NAME = philo

FILENAMES = main.c\
error_check.c\
utils.c\
utils1.c\
time.c\
init.c\
threads.c\
simulation.c\
actions.c\
monitoring.c\

CC = cc

CFLAGS = -Werror -Wall -Wextra

THREAD = -pthread

OBJS	:= ${FILENAMES:.c=.o}

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(THREAD) $(FILENAMES) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
