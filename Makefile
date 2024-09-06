SRCS = main.o \
./get_next_line/get_next_line.o ./get_next_line/get_next_line_utils.o\
./simple_parsing_fred/check_argument.o\
./simple_parsing_fred/error_message.o\
./simple_parsing_fred/open_file.o\
./simple_parsing_fred/analyse_map.o\
./simple_parsing_fred/copy_map.o\
./simple_parsing_fred/display_parsing.o\
./simple_parsing_fred/parse_element.o\
./simple_parsing_fred/parse_map.o\
./simple_parsing_fred/parsing_utils.o\

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
