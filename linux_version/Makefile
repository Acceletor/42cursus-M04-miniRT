NAME = miniRT

INC = -Iinclude -I$(MLX_DIR)
OBJ_DIR = obj
LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

MLX_DIR = minilibx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

LIB_FLAGS = -lm

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
	render/core_render \
	render/ren_ray_cal \
	render/ren_color_cal \
	render/ren_utils \
	render/ren_sphere \
	render/ren_plane \
	render/ren_cylinder \
	render/ren_cylinder_cap \
	render/ren_cylinder_side \
	render/ren_cone \
	math/vector_op \
	math/vector_op2

SRC = $(addsuffix .c, $(addprefix sources/, $(SRCBASE)))

OBJ = $(SRC:sources/%.c=$(OBJ_DIR)/%.o)

# start: 
# @make all

# macos: init_macos $(NAME)

# init_macos:
# 	MLX_DIR = libmlx/macos
# 	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
# 	@make -C ./libmlx/macos
# 	@cp libmlx/macos/libmlx.dylib .
# 	@echo "\033[32m[Macos Program is ready for use]\033[0m"

all: $(NAME)
	@echo "\033[32m[Program is ready for use]\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/math
	@mkdir -p $(OBJ_DIR)/render
	@make -C ./libft
	@make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: sources/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(LIB_FLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./libft
# @make clean -C $(MLX_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft
# @make fclean -C $(MLX_DIR)
# @$(RM) ./libmlx.dylib

re: fclean all

.PHONY: start all clean fclean re