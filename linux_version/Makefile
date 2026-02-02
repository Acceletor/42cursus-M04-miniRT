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
	core_error \
	core_gc \
	core_init \
	core_util \
	core_parse \
	parse_input_validator \
	parse_utils print_scene \
	parse_ambient parse_camera \
	parse_light parse_sphere \
	parse_plane parse_cylinder \
	vector_op \
	vector_op2 \
	ren_rendering \
	ren_intersection \
	ren_intersection_cy \
	convert_to_rgb \
	ren_hit_object_update \
	ren_ray_cal ren_color_cal

SRC = $(addsuffix .c, $(addprefix sources/, $(SRCBASE)))

OBJ = $(SRC:sources/%.c=$(OBJ_DIR)/%.o)

start: 
	@make all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@make -C ./libft
	@make -C ./minilibx

all: $(NAME)

$(OBJ_DIR)/%.o: sources/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(LIB_FLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: start all clean fclean re