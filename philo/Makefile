CFILES = philosophers.c philo_routine.c utils.c utils2.c
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra
CC = cc

NAME = philo

all : $(NAME)

$(NAME) : $(OFILES) philosophers.h
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OFILES)
fclean: clean
	rm -rf $(NAME)
re: fclean all
