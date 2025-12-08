#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <fcntl.h> 
# include <stdbool.h>
# include <unistd.h>
# include "../libmlx/macos/mlx.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "structs.h"

// core_error.c
void ft_err(char *str, t_collector **g_root);

//core_util.c
int invalid_file(int argc, char **argv, t_data *data);

// core_gc.c (manual garbage collector)
void gc_free_all(t_collector **g_root);
t_collector *new_node(void *adr);
int gc_append_adr(t_collector **g_root, void *adr);
void * gc_malloc(t_collector **g_root ,size_t size);

//core_init.c
int allocate_scene(t_data *data);






#endif