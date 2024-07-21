CC = cc
CFLAGS = -Wall -Wextra -Werror  

CFILES = philo.c utils.c routine.c
OFILES = $(CFILES:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	rm -rf $(OFILES)

fclean : clean
	rm -rf $(NAME)
re: fclean all

out: all
	./philo 5 1000 200 100