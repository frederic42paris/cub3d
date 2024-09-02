SRCS = main.o \

MINILIBX = ./minilibx/libmlx_Linux.a -lXext -lX11

NAME = cub3d

all: $(NAME)

$(NAME): $(SRCS)
	cc -Wall -Wextra -Werror -o $(NAME) $(SRCS) $(MINILIBX) -lm

%.o:%.c 
	cc -Wall -Wextra -Werror -o $@ -c $<

clean:
	rm -f $(SRCS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re