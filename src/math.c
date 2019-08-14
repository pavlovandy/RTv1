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

t_vector	vector_prod(t_vector v1, t_vector v2)
{
	t_vector	res;

	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = v1[0] * v2[2] - v1[2] * v2[0];
	res[2] = v1[1] * v2[0] - v1[0] * v2[1];
	return (res);
}

double		vect_len(t_vector a)
{
	return (sqrt(dot_prod(a, a)));
}

t_vector	multi_vect(t_vector a, double multi)
{
	return (t_vector){a[0] * multi, a[1] * multi, a[2] * multi};
}

t_vector	rotate_vector_around_x(t_vector a, t_pov *pov)
{
	t_vector	res;

	res[0] = a[0];
	res[1] = a[1] * pov->cx - a[2] * pov->sx;
	res[2] = a[1] * pov->sx + a[2] * pov->cx;
	return (res);
}

t_vector	rotate_vector_around_y(t_vector a, t_pov *pov)
{
	t_vector	res;

	res[0] = a[0] * pov->cy + a[2] * pov->sy;
	res[1] = a[1];
	res[2] = -a[0] * pov->sy + a[2] * pov->cy;
	return (res);
}

/*
**
**	matrix_rot_y * matrix_rot_x
**	cos(y)	sin(y)sin(x)	sin(y)cos(x)
**	0		cos(x)			-sin(x)
**	-sin(y)	cos(y)*sin(x)	cos(y)*cos(x)
**
*/

t_vector	rotate_around_x_y(t_vector a, t_pov pov)
{
	t_vector	res;

	res[0] = pov.cy * a[0] + pov.sx * pov.sy * a[1] + pov.sy * pov.cx * a[2];
	res[1] = pov.cx * a[1] - pov.sy * a[2];
	res[2] = -pov.sy * a[0] + pov.cy * pov.sx * a[1] + pov.cy * pov.sx * a[2];
	return (res);
}

t_vector	ft_rotate_camera(t_vector direction, t_pov *pov)
{
	double new_x;
	double new_y;
	double new_z;
	double angle1;
	double angle2;

	angle1 = pov->dir[1] / 180.0 * 3.14;
	angle2 = pov->dir[0] / 180.0 * 3.14;
	new_x = direction[0] * cos(angle1) + direction[2] * sin(angle1);
	new_y = direction[1];
	new_z = -direction[0] * sin(angle1) + direction[2] * cos(angle1);
	direction[0] = new_x;
	direction[1] = new_y;
	direction[2] = new_z;
	new_x = direction[0];
	new_y = direction[1] * cos(angle2) + direction[2] * sin(angle2);
	new_z = -direction[1] * sin(angle2) + direction[2] * cos(angle2);
	direction[2] = new_x;
	direction[2] = new_y;
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
