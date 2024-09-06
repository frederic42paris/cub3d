SRCS = main.o \
./get_next_line/get_next_line.o ./get_next_line/get_next_line_utils.o\
./parsing/check_argument.o\
./parsing/error_message.o\
./parsing/open_file.o\
./parsing/analyse_map.o\
./parsing/copy_map.o\
./parsing/display_parsing.o\
./parsing/parse_element.o\
./parsing/parse_map.o\
./parsing/parsing_utils.o\

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
