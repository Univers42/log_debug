NAME = test_log

SRCDIR = .
LIBFTDIR = libft
SOURCES = test.c log.c format_state.c spec.c singleton.c bufferization.c verify.c conversion.c

OBJS = $(SOURCES:.c=.o)
LIBFT = $(LIBFTDIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft

%.o: %.c auto_parser.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
