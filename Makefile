NAME = cub3D
CC   = cc -Wall -Wextra -Werror
RM   = rm -f
SRCS = lib/ft_atoi.c lib/ft_calloc.c lib/ft_empty.c lib/ft_isdigit.c lib/ft_max.c \
	lib/ft_memset.c lib/ft_puterror.c lib/ft_putstr_fd.c lib/ft_split.c lib/ft_strchr.c \
	lib/ft_strcmp.c lib/ft_strdup.c lib/ft_strjoin.c lib/ft_strlen.c lib/ft_strrchr.c \
	lib/ft_strtrim.c lib/ft_substr.c lib/get_next_line.c \
	parser/parse_map.c parser/parse_textures.c parser/parser.c parser/parser_utils.c \
	render/mouvments.c render/raycasting.c render/rendering.c render/texturing.c render/utils.c \
	main.c ft_free.c
OBJ  = $(SRCS:.c=.o)
INC  = include/cub3d.h include/libft.h

MLX    = -framework Cocoa -framework OpenGL -framework IOKit
MLXINC = -Iinclude -lglfw -L"/Users/$(USER)/homebrew/Cellar/glfw/3.3.8/lib/"
LIBMLX = /Users/$(USER)/MLX42/build/libmlx42.a
INCLUDEDIRS = -I /Users/$(USER)/MLX42/include/MLX42/ -I ./include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LIBMLX) $(MLX) $(MLXINC)  $^ -o $@

%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(INCLUDEDIRS)


clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean all clean re

