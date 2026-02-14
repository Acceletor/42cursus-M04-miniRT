/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:03:33 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:20:58 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.gc_root = NULL;
	data.fd = -1;
	if (invalid_file(argc, argv, &data))
		ft_err("Incorrect argument: ./miniRT file_name.rt", &data.gc_root, 1);
	init_scene(&data);
	parse(&data);
	print_scene(&data);
	rendering(&data);
	gc_free_all(&data.gc_root);
	return (0);
}
