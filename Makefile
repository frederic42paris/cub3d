SRCS = main.o \
./get_next_line/get_next_line.o ./get_next_line/get_next_line_utils.o\

MINILIBX = ./minilibx/libmlx_Linux.a -lXext -lX11

NAME = cub3d

all: libft $(NAME)

$(NAME): $(SRCS)
	cc -Wall -Wextra -Werror -o $(NAME) $(SRCS) $(MINILIBX) -lm -L libft -lft

%.o:%.c 
	cc -Wall -Wextra -Werror -o $@ -c $<

libft:
	cd libft ; make

clean:
	rm -f $(SRCS)
	cd libft ; make clean

fclean: clean
	rm -f $(NAME)
	cd libft ; make fclean

re: fclean all

.PHONY: all clean fclean re libft
