NAME = hotrace
HEADER = hotrace.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
SRC = main.c hash_table.c utilice.c utilice1.c utilice2.c
OBJS = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all
