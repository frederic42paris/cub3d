SRCS = main.c \
./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c\
./simple_parsing_fred/check_argument.c\
./simple_parsing_fred/error_message.c\
./simple_parsing_fred/open_file.c\
./simple_parsing_fred/analyse_map.c\
./simple_parsing_fred/copy_map.c\
./simple_parsing_fred/display_parsing.c\
./simple_parsing_fred/parse_element.c\
./simple_parsing_fred/parse_map.c\
./simple_parsing_fred/parsing_utils.c\
./raycasting/raycasting.c\

MINILIBX = ./minilibx/libmlx_Linux.a -lXext -lX11

OBJS = ${SRCS:.c=.o}

NAME = cub3d

all: libft $(NAME)

$(NAME): $(OBJS)
	cc -Wall -Wextra -Werror -o $(NAME) $(OBJS) $(MINILIBX) -lm -L libft -lft

%.o:%.c 
	cc -Wall -Wextra -Werror -o $@ -c $<

libft:
	cd libft ; make

clean:
	rm -f $(OBJS)
	cd libft ; make clean

fclean: clean
	rm -f $(NAME)
	cd libft ; make fclean

re: fclean all

.PHONY: all clean fclean re libft
