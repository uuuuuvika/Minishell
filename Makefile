cc		= cc
CFLAGS  = -Wall -Werror -Wextra -Iinclude
LDFLAGS = -lreadline #-lhistory

SRCDIR = src  
OBJDIR = build 

SOURCES := $(shell find $(SRCDIR) -name '*.c')  
OBJECTS := $(SOURCES:.c=.o)

$(OBJDIR):
		mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
		$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all: minishell

minishell: $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f minishell

re: fclean all