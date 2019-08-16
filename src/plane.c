/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:32:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/05 14:32:40 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		plane_cal(t_pixel_cal *pc, t_plane_data *data)
{
	pc->intersect_point = pc->eye_point + \
							multi_vect(pc->eye_point_dir, pc->closest_dist);
	if (pc->sign > 0)
		pc->normal = data->normal;
	else
		pc->normal = -data->normal;
	pc->specular = data->specular;
	pc->color = data->color;
	pc->to_eye_dir = -pc->eye_point_dir;
}

t_roots		plane_roots(t_vector eye, t_vector eye_dir, \
												void *data, t_pixel_cal *pc)
{
	t_plane_data	*plane;

	plane = (t_plane_data*)data;
	pc->dp_d_v = dot_prod(eye_dir, plane->normal);
	if (comp_real(pc->dp_d_v, 0, 0.00001))
		return ((t_roots){BIG_VALUE, BIG_VALUE});
	pc->dp_x_v = dot_prod(eye - plane->dot, plane->normal);
	return ((t_roots){BIG_VALUE, -pc->dp_x_v / pc->dp_d_v});
}

int			read_plane_data(int fd, t_plane_data *data)
{
	if (check_line_for_char(fd, '{'))
		return (1);
	if (check_line_for_coord(fd, &data->normal, "normal : {"))
		return (1);
	if (make_unit_vector(&data->normal))
		return (error_message(TRED"Normal vector is 0-vector"TNULL));
	if (check_line_for_coord(fd, &data->dot, "dot : {"))
		return (1);
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
