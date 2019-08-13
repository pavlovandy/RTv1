/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:49:46 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/12 17:49:47 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		cylin_cal(t_pixel_cal *pc, t_cylin_data	*cylin)
{
	float	m;

	pc->intersect_point = pc->eye_point + multi_vect(pc->eye_point_dir, pc->closest_dist);
	m = dot_prod(pc->eye_point_dir, cylin->dir) * pc->closest_dist + dot_prod(pc->oc, cylin->dir);
	pc->color = cylin->color;
	pc->normal = pc->intersect_point - cylin->dot - multi_vect(cylin->dir, m);
	make_unit_vector(&pc->normal);
	pc->to_eye_dir = - pc->eye_point_dir;
	pc->specular = cylin->specular;
}		

t_roots		cylin_roots(t_vector eye, t_vector eye_dir, void *data, t_pixel_cal *pc)
{
	t_cylin_data	*cylin;

	cylin = (t_cylin_data*)data;
	pc->oc = eye - cylin->dot;
	pc->dp_x_v = dot_prod(pc->oc, cylin->dir);
	pc->dp_d_v = dot_prod(eye_dir, cylin->dir);

	pc->a = dot_prod(eye_dir, eye_dir) - pc->dp_d_v * pc->dp_d_v;
	pc->b = dot_prod(eye_dir, pc->oc) - pc->dp_d_v * pc->dp_x_v;
	pc->c = dot_prod(pc->oc, pc->oc) - pc->dp_x_v * pc->dp_x_v - cylin->radius * cylin->radius;
	pc->d = pc->b * pc->b - pc->a * pc->c;
	if (pc->d < 0)
		return ((t_roots){BIG_VALUE, BIG_VALUE});
	pc->d = sqrt(pc->d);
	return ((t_roots){(-pc->b + pc->d) / (pc->a), (-pc->b - pc->d) / (pc->a)});
}

int		read_cylin_data(int fd, t_cylin_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->dot, "dot : {"))
		return (1);
	if (check_line_for_value(fd, &data->radius, "radius : {"))
		return (1);
	if (data->radius <= 0)
		return (error_message(TRED"Negative radius of cylin detected"TNULL));
	if (check_line_for_coord(fd, &data->dir, "dir : {"))
		return (1);
	printf("ya tut %f\n", vect_len(data->dir));
	if (make_unit_vector(&data->dir))
		return (error_message(TRED"Directional vector is 0-vector"TNULL));
	printf("ya tut %f\n", vect_len(data->dir));
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
