NAME = so_long

SRC = so_long.c \
	  read_map.c \
	  handle_key.c \
	  load_image.c \
	  check_map.c \
      gnl/get_next_line.c \
      gnl/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C minilibx
		mv minilibx/libmlx.a .
		gcc -Wall -g -Werror -Wextra -c $(SRC)
		gcc -Wall -g -Werror -Wextra -L. -lmlx -framework OpenGL -framework Appkit $(OBJ) -o $(NAME)

clean:
		make -C minilibx clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx clean
		rm -rf $(NAME) $(OBJ)

re : fclean all
