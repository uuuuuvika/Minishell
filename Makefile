cc		= cc
CFLAGS  = -Wall -Werror -Wextra -Iinclude -Ilib/libft
LDFLAGS = -lreadline -L./lib/libft -lft #-lhistory

SRCDIR = src
SOURCES := $(shell find $(SRCDIR) -name '*.c')  
OBJECTS := $(SOURCES:.c=.o)
LIBFT = lib/libft/libft.a 

$(LIBFT) :
	$(MAKE) -C ./lib/libft

all: minishell

minishell: $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	$(MAKE) -C ./lib/libft clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C ./lib/libft fclean
	rm -rf minishell

re: fclean all
