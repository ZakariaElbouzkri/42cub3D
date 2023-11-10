NAME = cub3d
CC   = gcc -Wall -Wextra -Werror -fsanitize=address -g
RM   = rm -f
SRCS = lib/ft_atoi.c lib/ft_calloc.c lib/ft_isalnum.c lib/ft_isalpha.c lib/ft_isascii.c lib/ft_isdigit.c lib/ft_isprint.c lib/ft_itoa.c lib/ft_memcmp.c lib/ft_memcpy.c lib/ft_memmove.c lib/ft_memset.c lib/ft_printf.c lib/ft_putchar.c lib/ft_putchar_fd.c lib/ft_putendl_fd.c lib/ft_puterror.c lib/ft_puthexa.c lib/ft_putnbr.c lib/ft_putnbr_fd.c lib/ft_putptr.c lib/ft_putstr.c lib/ft_putstr_fd.c lib/ft_putunbr.c lib/ft_split.c lib/ft_strchr.c lib/ft_strchr_std.c lib/ft_strcmp.c lib/ft_strcpy.c lib/ft_strdup.c lib/ft_striteri.c lib/ft_strjoin.c lib/ft_strjoin_std.c lib/ft_strlcpy.c lib/ft_strlen.c lib/ft_strmapi.c lib/ft_strncmp.c lib/ft_strndup.c lib/ft_strnstr.c lib/ft_strrchr.c lib/ft_strtrim.c lib/ft_substr.c lib/ft_swap.c lib/ft_tolower.c lib/ft_toupper.c lib/get_next_line.c main.c \
	parser/parse_map.c parser/parse_textures.c parser/parser.c parser/parser_utils.c parser/rgb_to_hex.c \
	render/rendering.c render/raycasting.c
#render/render_game.c 
OBJ  = $(SRCS:.c=.o)
INC  = include/cub3d.h include/libft.h 

MLX    = -framework Cocoa -framework OpenGL -framework IOKit
MLXINC = -Iinclude -lglfw -L"/Users/$(USER)/homebrew/Cellar/glfw/3.3.8/lib/"
LIBMLX = /Users/$(USER)/MLX42/build/libmlx42.a
INCLUDEDIRS = -I /Users/$(USER)/MLX42/include/MLX42/ -I ./include

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(LIBMLX) $(MLX) $(MLXINC)  $^ -o $@
	@echo "\033[1;32m$@ is created\033[0m"

%.o: %.c $(INC)
	@$(CC) -c $< -o $@ $(INCLUDEDIRS)
	@echo "compiling $< ... \033[1;36mDone\033[0m"
	@sleep 0.02
	@clear

clean:
	@$(RM) $(OBJ)
	@echo "Object files removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "everything cleaned"

re: fclean all

.PHONY: fclean all clean re

