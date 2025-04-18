NAME = hotrace
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c hash_table.c utilice.c \
	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.cpp
	$(CPP) $(CFLAGS) $< -c -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all
