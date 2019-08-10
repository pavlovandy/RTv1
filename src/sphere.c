/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:32:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_roots		sphere_roots(t_vector view_point, t_vector view_port, t_sphere_data *sphere)
{
	t_vector	vr;
	float		a;
	float		b;
	float		c;
	float		d;

	vr = view_point - sphere->cent;
	a = dot_prod(view_port, view_port);
	b = 2 * dot_prod(vr, view_port);
	c = dot_prod(vr, vr) - sphere->radius * sphere->radius;

	d = b * b - 4 * a * c;
	if (d < 0)
		return ((t_roots){BIG_VALUE, BIG_VALUE});
	return ((t_roots){(-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)});
}

int		read_sphere_data(int fd, t_sphere_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->cent, "cent : {"))
		return (1);
	if (check_line_for_value(fd, &data->radius, "radius : {"))
		return (1);
	if (data->radius <= 0)
		return (error_message(TRED"Negative radius of sphere detected"TNULL));
	if (check_line_for_coord(fd, &data->color, "color : {"))
		return (1);
	if (data->color[0] > 255 || data->color[1] > 255 || data->color[2] > 255)
		return (error_message(TRED"Bad color values"TNULL));
	if (data->color[0] < 0 || data->color[1] < 0 || data->color[2] < 0)
		return (error_message(TRED"Bad color values"TNULL));
	if (check_line_for_int_value(fd, &data->specular, "specular : {"))
		return (1);
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
