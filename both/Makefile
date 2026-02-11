NAME = miniRT

# Directories
INC = -Iinclude 
OBJ_DIR = obj
LIBFT = ./libft/libft.a

# Complier
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
	MLX_DIR = libmlx/macos
	MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	LIB_FLAGS =
	MLX_LIB   = $(MLX_DIR)/libmlx.dylib
	COPY_MLX  = cp -f $(MLX_LIB) .
else
	MLX_DIR = libmlx/linux
	MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11
	LIB_FLAGS = -lm
	MLX_LIB   = 
	COPY_MLX  = true
endif

# Sources
SRCBASE = \
	main \
	core_init \
	utils/core_error \
	utils/core_gc \
	utils/core_util \
	utils/convert_to_rgb \
	utils/print_scene \
	parser/core_parse \
	parser/parse_input_validator \
	parser/parse_utils \
	parser/parse_ambient \
	parser/parse_camera \
	parser/parse_light \
	parser/parse_sphere \
	parser/parse_plane \
	parser/parse_cylinder \
	parser/parse_cone \
	parser/parse_tube \
	parser/parse_circle \
	render/core_render \
	render/ren_ray_cal \
	render/ren_color_cal \
	render/ren_utils \
	render/ren_sphere \
	render/ren_plane \
	render/ren_circle \
	render/ren_cylinder \
	render/ren_cylinder_side \
	render/ren_cone \
	render/ren_cone_side \
	math/vector_op \
	math/vector_op2

SRC = $(addsuffix .c, $(addprefix sources/, $(SRCBASE)))
OBJ = $(SRC:sources/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@$(COPY_MLX)
	@echo "\033[32m[Program is ready for use]\033[0m"

start:
	@make all

# Build libft libraries
$(LIBFT):
	@make -C ./libft
mlx:
	@make -C $(MLX_DIR)

# Ensure obj directory exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/math
	@mkdir -p $(OBJ_DIR)/render

# compile objects
$(OBJ_DIR)/%.o: sources/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -I$(MLX_DIR) -c $< -o $@

# Link
$(NAME): $(OBJ) $(LIBFT) mlx
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(LIB_FLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./libft
	@make clean -C $(MLX_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft
	@rm -f ./libmlx.dylib

re: fclean all

.PHONY: start all mlx clean fclean re