SRCS	= minishell.c
OBJS	= $(SRCS:.c=.o)
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
LDFLAGS = -lreadline #-lhistory

all: minishell

minishell: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f minishell

re: fclean all