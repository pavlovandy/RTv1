/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/14 12:58:54 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		sphere_cal(t_pixel_cal *pc, t_sphere_data *data)
{
	pc->intersect_point = pc->eye_point + \
							multi_vect(pc->eye_point_dir, pc->closest_dist);
	pc->normal = pc->intersect_point - data->cent;
	make_unit_vector(&pc->normal);
	pc->specular = data->specular;
	pc->to_eye_dir = -pc->eye_point_dir;
	pc->color = data->color;
}

t_roots		sphere_roots(t_vector eye, t_vector eye_dir, \
												void *data, t_pixel_cal *pc)
{
	t_sphere_data	*sphere;

	sphere = (t_sphere_data*)data;
	pc->oc = eye - sphere->cent;
	pc->a = dot_prod(eye_dir, eye_dir);
	pc->b = dot_prod(pc->oc, eye_dir);
	pc->c = dot_prod(pc->oc, pc->oc) - sphere->radius * sphere->radius;
	pc->d = pc->b * pc->b - pc->a * pc->c;
	if (pc->d < 0)
		return ((t_roots){BIG_VALUE + 1, BIG_VALUE + 1});
	pc->d = sqrt(pc->d);
	return ((t_roots){(-pc->b + pc->d) / (pc->a), (-pc->b - pc->d) / (pc->a)});
}

int			read_sphere_data(int fd, t_sphere_data *data)
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
	if (data->specular < -1 || data->specular > 1000)
		return (error_message(TRED"Bad specular values"TNULL));
	if (check_line_for_char(fd, '}'))
		return (1);
	return (0);
}
