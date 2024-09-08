SRCS = main.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	parsing_fred/store_data.c \
	parsing_fred/check_argument.c \
	parsing_fred/display_parsing.c \
	parsing_fred/open_file.c \
	parsing_fred/parsing_utils.c \
	parsing_fred/parsing_utils2.c \
	parsing_fred/store_textures.c \
	parsing_fred/store_map.c \
	parsing_fred/measure_map.c \
	parsing_fred/find_player.c \
	parsing_fred/check_text_id.c \
	parsing_fred/check_text_dup.c \
	parsing_fred/check_text_path.c \
	parsing_fred/check_text_rgb.c \
	parsing_fred/check_map_walls.c \
	parsing_fred/check_map_character.c \
	parsing_fred/check_map_players.c \
	parsing_fred/check_map_line.c \
	parser/init.c \
	parser/parsing_utils.c \
	parser/parsing_utils2.c \
	parser/parsing_utils3.c \
	parser/map_builder_utils.c \
	parser/map_checker.c \
	parser/map_checker_utils.c \
	parser/map_checker_utils2.c \
	parser/rgb_checks.c \
	raycasting/raycasting.c\


MINILIBX = ./minilibx/libmlx_Linux.a -lXext -lX11

OBJDIR = .obj

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

NAME = cub3d

all: libft $(NAME)

$(NAME): $(OBJS)
	cc -Wall -Wextra -Werror -o $(NAME) $(OBJS) $(MINILIBX) -lm -L libft -lft

$(OBJDIR)/%.o : %.c
	mkdir -p $(dir $@)
	cc -g3 -Wall -Wextra -Werror -o $@ -c $<

libft:
	cd libft ; make

clean:
	rm -rf $(OBJDIR)
	cd libft ; make clean

fclean: clean
	rm -rf $(NAME)
	cd libft ; make fclean

re: fclean all

.PHONY: all clean fclean re libft

# simple_parsing_fred/parse_element.c \
# parsing_fred/error_message.c \
# simple_parsing_fred/parse_map.c \