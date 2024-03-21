cc		= cc
CFLAGS  = -Wall -Werror -Wextra -Iinclude
LDFLAGS = -lreadline #-lhistory

SRCDIR = src  

SOURCES := $(shell find $(SRCDIR) -name '*.c')  
OBJECTS := $(SOURCES:.c=.o)

all: minishell

minishell: $(OBJECTS)
		$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf minishell

re: fclean all