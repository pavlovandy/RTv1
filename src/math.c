/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:17 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:32:17 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double		dot_prod(t_vector v1, t_vector v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] \
			+ v1[2] * v2[2]);
}

double		vect_len(t_vector a)
{
	return (sqrt(dot_prod(a, a)));
}

t_vector	multi_vect(t_vector a, double multi)
{
	return (t_vector){a[0] * multi, a[1] * multi, a[2] * multi};
}

t_vector	ft_rotate_camera(t_vector direction, t_pov *pov)
{
	double new_x;
	double new_y;
	double new_z;

	new_x = direction[0] * pov->cy + direction[2] * pov->sy;
	new_z = -direction[0] * pov->sy + direction[2] * pov->cy;
	direction[0] = new_x;
	direction[2] = new_z;
	new_y = direction[1] * pov->cx + direction[2] * pov->sx;
	new_z = -direction[1] * pov->sx + direction[2] * pov->cx;
	direction[1] = new_y;
	direction[2] = new_z;
	return (direction);
}

int			make_unit_vector(t_vector *v)
{
	double	v_len;

	v_len = vect_len(*v);
	if (comp_real(v_len, 0, 0.00001))
		return (1);
	*v = multi_vect(*v, 1 / v_len);
	return (0);
}
