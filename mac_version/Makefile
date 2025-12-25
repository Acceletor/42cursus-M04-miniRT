NAME = miniRT

# Directories
INC = -Iinclude
OBJ_DIR = obj/
LIBFT = ./libft/libft.a

# Complier
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

# libmlx

MLX_DIR = libmlx/macos
MLX_FLAGS =  -I$(MLX_DIR) -L$(MLX_DIR)\
			-lmlx -framework OpenGL \
			-framework AppKit
# MLX_RPATH = 

SRCBASE = main core_error core_gc core_init core_util core_parse \
		parse_input_validator parse_utils print_scene \
		parse_ambient parse_camera parse_light parse_sphere \
		parse_plane parse_cylinder vector_op rendering \

SRC = $(addsuffix .c, $(addprefix sources/, $(SRCBASE)))

OBJ = $(SRC:sources/%.c=$(OBJ_DIR)%.o)

start:
	@make all

# Ensure obj directory exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build libft libraries
	@make -C ./libft
	@make -C ./libmlx/macos

# Build executable
all: $(NAME)
	@cp libmlx/macos/libmlx.dylib .
	@echo "\033[32m[Program is ready for use]\033[0m"

# Rule to compile object files
$(OBJ_DIR)%.o: sources/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -I$(MLX_DIR) -c $< -o $@

# Link everything
$(NAME): $(OBJ)
	@make -C ./libft
	@make -C ./libmlx/macos
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) \
	$(MLX_FLAGS) $(MLX_RPATH) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./libmlx/macos
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft
	@ rm -f ./libmlx.dylib

re: fclean all

.PHONY: start all clean fclean re