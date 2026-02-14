/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej&ksuebtha <student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:04:50 by sandrzej&ks       #+#    #+#             */
/*   Updated: 2026/02/14 18:33:30 by sandrzej&ks      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec	sub_vec(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	add_vec(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_vec	mult_vec(t_vec v, double a)
{
	t_vec	w;

	w.x = v.x * a;
	w.y = v.y * a;
	w.z = v.z * a;
	return (w);
}

t_vec	hadamard(t_vec a, t_vec b)
{
	return ((t_vec){a.x * b.x, a.y * b.y, a.z * b.z});
}
